#include "StatusManager.h"

namespace OpenXcom
{
// Initialize the static instance
StatusManager* StatusManager::instance = nullptr;

YAML::YamlRootNodeReader Status::getReader() const
{
    if (!hasData())
    {
		return YAML::YamlRootNodeReader("", "status_data", false);
    }
    return YAML::YamlRootNodeReader(getData(), "status_data", false);
}

TimeBasedStatus::TimeBasedStatus(float duration)
	: duration(duration), elapsedTime(0.f) {}

void TimeBasedStatus::update(float deltaTime)
{
	elapsedTime += deltaTime;
	if (elapsedTime >= duration)
	{
		delete this;
	}
}

bool TimeBasedStatus::isExpired() const
{
	return elapsedTime >= duration;
}

CounterBasedStatus::CounterBasedStatus(int count)
	: count(count) {}

void CounterBasedStatus::decrementCount()
{
	if (count > 0)
	{
		count--;
	}
}
void CounterBasedStatus::addToCount(int amount)
{
	count += amount;
}

bool CounterBasedStatus::isExpired() const
{
	return count <= 0;
}

void CounterBasedStatus::update(float /*deltaTime*/) {}

StatusManager* StatusManager::getInstance()
{
	if (instance == nullptr)
	{
		instance = new StatusManager();
	}
	return instance;
}

void StatusManager::addStatus(const std::string& identifier, StatusPtr status)
{
	statuses[identifier].push_back(std::move(status));
}

bool StatusManager::hasStatus(const std::string& identifier) const
{
	auto it = statuses.find(identifier);
    return it != statuses.end() && !it->second.empty();
}

void StatusManager::removeStatus(const std::string& identifier)
{
	auto it = statuses.find(identifier);
    if (it != statuses.end() && !it->second.empty())
    {
        it->second.erase(it->second.begin());
    }
}

void StatusManager::update(float deltaTime)
{
	for (auto& pair : statuses)
    {
        auto& statusList = pair.second;
        auto it = statusList.begin();
        while (it != statusList.end())
        {
            (*it)->update(deltaTime);

            if (*it && (*it)->isExpired())
            {
                it = statusList.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }
}

Status* StatusManager::getStatus(const std::string& identifier)
{
	auto it = statuses.find(identifier);
    if (it != statuses.end() && !it->second.empty())
    {
        return it->second.front().get();
    }
    return nullptr;
}

std::vector<std::pair<std::string, Status*> > StatusManager::getStatusesByPrefix(const std::string& prefix) const
{
	std::vector<std::pair<std::string, Status*>> result;
    for (const auto& pair : statuses)
    {
        const std::string& key = pair.first;
        const std::vector<StatusPtr>& list = pair.second;
        if (key.size() >= prefix.size() && key.substr(0, prefix.size()) == prefix)
        {
            for (const auto& statusPtr : list)
            {
                if (statusPtr)
                {
                    result.emplace_back(key, statusPtr.get());
                }
            }
        }
    }
    return result;
}

std::vector<std::string> StatusManager::getActiveIdentifiers() const
{
	std::vector<std::string> identifiers;
    for (const auto& pair : statuses)
    {
        if (!pair.second.empty())
        {
            identifiers.push_back(pair.first);
        }
    }
    return identifiers;
}

}
