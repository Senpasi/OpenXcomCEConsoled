#include "StreamerConsoleConnector.h"
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>

namespace OpenXcom
{

static const wchar_t* PIPE_NAME = L"\\\\.\\pipe\\game-event-pipe";
static const wchar_t* PIPE_NAME_WRITE = L"\\\\.\\pipe\\game-event-pipe-response";
static const size_t MAX_SEND_QUEUE_SIZE = 100;
static const size_t MAX_RECEIVE_QUEUE_SIZE = 100;
static bool pipeErrorReported = false;

StreamerConsoleConnector::StreamerConsoleConnector()
	: stopFlag_(false), stopEvent_(nullptr)
{
	stopEvent_ = CreateEvent(nullptr, TRUE, FALSE, nullptr);
	if (!stopEvent_)
	{
		std::cerr << "Failed to create stop event" << std::endl;
		return;
	}
}

StreamerConsoleConnector::~StreamerConsoleConnector()
{
	stop();
	if (stopEvent_)
		CloseHandle(stopEvent_);
}

void StreamerConsoleConnector::start()
{
	readThread_ = std::thread(&StreamerConsoleConnector::processRead, this);
	writeThread_ = std::thread(&StreamerConsoleConnector::processWrite, this);
}

void StreamerConsoleConnector::stop()
{
	if (stopFlag_)
		return;
	stopFlag_ = true;
	SetEvent(stopEvent_);

	// Wake up threads waiting on condition variables
	cvReceive_.notify_one();
	cvSend_.notify_one();

	if (readThread_.joinable())
	{
		readThread_.join();
	}
	if (writeThread_.joinable())
	{
		writeThread_.join();
	}
}

void StreamerConsoleConnector::processRead()
{
	while (!stopFlag_)
	{
		HANDLE hPipe = CreateNamedPipeW(
			PIPE_NAME,
			PIPE_ACCESS_DUPLEX | FILE_FLAG_OVERLAPPED,
			PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT,
			1,
			65536, 65536,
			5000, // 5 seconds
			nullptr);

		if (hPipe == INVALID_HANDLE_VALUE)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			continue;
		}

		OVERLAPPED connectOverlapped = {};
		connectOverlapped.hEvent = CreateEvent(nullptr, TRUE, FALSE, nullptr);
		if (!connectOverlapped.hEvent)
		{
			CloseHandle(hPipe);
			continue;
		}

		// async connect
		BOOL connected = ConnectNamedPipe(hPipe, &connectOverlapped);
		DWORD err = GetLastError();

		if (!connected && err != ERROR_IO_PENDING && err != ERROR_PIPE_CONNECTED)
		{
			CloseHandle(connectOverlapped.hEvent);
			CloseHandle(hPipe);
			continue;
		}

		// wait connect or stop
		HANDLE waitHandles[] = {connectOverlapped.hEvent, stopEvent_};
		DWORD result = WaitForMultipleObjects(2, waitHandles, FALSE, INFINITE);

		if (result == WAIT_OBJECT_0 + 1) // stopEvent triggered
		{
			CancelIoEx(hPipe, &connectOverlapped);
			CloseHandle(connectOverlapped.hEvent);
			CloseHandle(hPipe);
			return;
		}

		if (err != ERROR_PIPE_CONNECTED)
		{
			if (!GetOverlappedResult(hPipe, &connectOverlapped, &err, FALSE))
			{
				CloseHandle(connectOverlapped.hEvent);
				CloseHandle(hPipe);
				continue;
			}
		}

		// connected - read message in loop
		char buffer[65536];
		while (!stopFlag_)
		{
			if (!consoleConnected_)
				consoleConnected_ = true;

			OVERLAPPED readOverlapped = {};
			readOverlapped.hEvent = CreateEvent(nullptr, TRUE, FALSE, nullptr);
			if (!readOverlapped.hEvent)
				break;

			DWORD bytesRead = 0;
			BOOL readResult = ReadFile(hPipe, buffer, sizeof(buffer) - 1, &bytesRead, &readOverlapped);
			err = GetLastError();

			if (!readResult && err == ERROR_IO_PENDING)
			{
				HANDLE readHandles[] = {readOverlapped.hEvent, stopEvent_};
				DWORD readWait = WaitForMultipleObjects(2, readHandles, FALSE, INFINITE);

				if (readWait == WAIT_OBJECT_0 + 1)
				{
					CancelIoEx(hPipe, &readOverlapped);
					CloseHandle(readOverlapped.hEvent);
					break;
				}

				if (!GetOverlappedResult(hPipe, &readOverlapped, &bytesRead, FALSE))
				{
					CloseHandle(readOverlapped.hEvent);
					break;
				}
			}
			else if (!readResult)
			{
				CloseHandle(readOverlapped.hEvent);
				break;
			}

			CloseHandle(readOverlapped.hEvent);

			if (bytesRead == 0)
				continue;

			buffer[bytesRead] = '\0';
			{
				std::lock_guard<std::mutex> lk(queueMutex_);
				if (receivedDataQueue_.size() >= MAX_RECEIVE_QUEUE_SIZE)
				{
					delete[] receivedDataQueue_.front();
					receivedDataQueue_.pop();
				}
				char* msg = new char[bytesRead + 1];
				strcpy(msg, buffer);
				receivedDataQueue_.push(msg);
			}
			cvReceive_.notify_one();
		}

		DisconnectNamedPipe(hPipe);
		CloseHandle(connectOverlapped.hEvent);
		CloseHandle(hPipe);
	}
}

void StreamerConsoleConnector::processWrite()
{
	while (!stopFlag_)
	{
		std::unique_lock<std::mutex> lk(queueMutex_);

		cvSend_.wait(lk, [this]
					 { return stopFlag_ || !sendDataQueue_.empty(); });

		if (stopFlag_)
			return;

		std::string data = sendDataQueue_.front();
		sendDataQueue_.pop();
		lk.unlock();

		// connect to server as client
		HANDLE hPipe = CreateFileW(
			PIPE_NAME_WRITE,
			GENERIC_READ | GENERIC_WRITE,
			0,
			nullptr,
			OPEN_EXISTING,
			FILE_FLAG_OVERLAPPED,
			nullptr);

		if (hPipe == INVALID_HANDLE_VALUE)
		{
			DWORD err = GetLastError();
			if (err != ERROR_PIPE_BUSY) // busy - try again
			{
				if (!pipeErrorReported)
				{
					std::cerr << "Failed send to pipe, error " << err << std::endl;
					pipeErrorReported = true;
				}
				continue;
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
			continue;
		}

		// check handler is pipe
		if (!SetNamedPipeHandleState(hPipe, nullptr, nullptr, nullptr))
		{
			CloseHandle(hPipe);
			continue;
		}

		OVERLAPPED writeOverlapped = {};
		writeOverlapped.hEvent = CreateEvent(nullptr, TRUE, FALSE, nullptr);
		if (!writeOverlapped.hEvent)
		{
			CloseHandle(hPipe);
			continue;
		}

		DWORD bytesWritten = 0;
		BOOL writeResult = WriteFile(hPipe, data.c_str(), (DWORD)data.size(), &bytesWritten, &writeOverlapped);
		DWORD err = GetLastError();

		if (!writeResult && err == ERROR_IO_PENDING)
		{
			HANDLE writeHandles[] = {writeOverlapped.hEvent, stopEvent_};
			DWORD writeWait = WaitForMultipleObjects(2, writeHandles, FALSE, 5000);

			if (writeWait == WAIT_OBJECT_0 + 1)
			{
				CancelIoEx(hPipe, &writeOverlapped);
				CloseHandle(writeOverlapped.hEvent);
				CloseHandle(hPipe);
				return;
			}

			GetOverlappedResult(hPipe, &writeOverlapped, &bytesWritten, FALSE);
		}

		CloseHandle(writeOverlapped.hEvent);
		CloseHandle(hPipe);
		pipeErrorReported = false;
	}
}

bool StreamerConsoleConnector::tryGetReceivedData(char** data)
{
	std::lock_guard<std::mutex> lk(queueMutex_);
	if (receivedDataQueue_.empty())
		return false;

	*data = receivedDataQueue_.front();
	receivedDataQueue_.pop();
	return true;
}

void StreamerConsoleConnector::sendData(const std::string& data)
{
	{
		std::lock_guard<std::mutex> lk(queueMutex_);
		if (sendDataQueue_.size() >= MAX_SEND_QUEUE_SIZE)
		{
			sendDataQueue_.pop();
		}
		sendDataQueue_.push(data);
	}
	cvSend_.notify_one();
}

}
