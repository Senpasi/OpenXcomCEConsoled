#pragma once
/*
 * Copyright 2025 Kirill Stepaniuk.
 *
 * This file is extension of OpenXcom.
 *
 * OpenXcom is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * OpenXcom is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with OpenXcom.  If not, see <http://www.gnu.org/licenses/>.
 */

#if defined(_WIN32)
#ifndef NOMINMAX
#define NOMINMAX
#endif
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

#include <condition_variable>
#include <mutex>
#include <queue>
#include <string>
#include <thread>

namespace OpenXcom
{

class StreamerConsoleConnector
{
  private:
	bool stopFlag_;
	HANDLE stopEvent_;
	std::mutex queueMutex_;
	std::condition_variable cvReceive_;
	std::condition_variable cvSend_;
	std::queue<char*> receivedDataQueue_;
	std::queue<std::string> sendDataQueue_;
	std::thread readThread_;
	std::thread writeThread_;
    std::atomic<bool> consoleConnected_{false};

	void processRead();
	void processWrite();

  public:
	StreamerConsoleConnector();
	~StreamerConsoleConnector();

	bool tryGetReceivedData(char** data);
	void sendData(const std::string& data);
	void start();
	void stop();
	bool isConnected() const { return consoleConnected_; };
};

}
