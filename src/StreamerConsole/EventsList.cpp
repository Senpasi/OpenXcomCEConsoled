#include "EventsList.h"
#include "../Engine/Logger.h"
#include "../Engine/Yaml.h"
#include <unordered_set>
namespace OpenXcom
{

EventsList::EventsList()
{
	statusManager = StatusManager::getInstance();
}

std::string EventsList::processEvent(const std::string& yamlString)
{
	std::string eventId = "";
	std::string message = "";
	YAML::YamlRootNodeReader reader(YAML::YamlString{yamlString}, "event_input", false);
	
	if (!reader.isValid())
	{
		Log(LOG_WARNING) << "Failed to parse event YAML.";
		return "Failed to parse event YAML.";
	}
	
	if (!reader.tryRead("event_id", eventId))
	{
		Log(LOG_WARNING) << "Missing 'event_id' in event YAML.";
		return "Missing 'event_id' in event YAML.";
	}

	if (!reader.tryRead("name", message))
	{
		message = "Запуск события '" + eventId + "'";
	}

	YAML::YamlString fullEventYaml = reader.emit();

	if ((eventId.rfind("reinforcement_", 0) == 0) || 
    (eventId.rfind("hiring_", 0) == 0) || 
    (eventId.rfind("custom_event_", 0) == 0))
	{
		auto status = std::make_unique<CounterBasedStatus>(1);
		status->setData(fullEventYaml);
		statusManager->addStatus(eventId, std::move(status)); // Добавляем в очередь

		Log(LOG_INFO) << "Queued event: " << eventId;
		return message;
	}

	std::unordered_set<std::string> counterEvents = {
		"geoscape_event",
		"ufo_and_bases_detect_all",
		"ask_info",
		"force_bug_hunt",
		"soldier_transformation",
		"soldier_message"
	};

	if (eventId == "increased_damage_5min")
    {
        auto status = std::make_unique<TimeBasedStatus>(300.f);
        status->setData(fullEventYaml);
        statusManager->addStatus("increased_damage", std::move(status));
	}
	else if (counterEvents.find(eventId) != counterEvents.end())
	{
		auto status = std::make_unique<CounterBasedStatus>(1);
		status->setData(fullEventYaml);
		statusManager->addStatus(eventId, std::move(status));
	}
	else
	{
		Log(LOG_WARNING) << "Unknown event received: " << eventId;
		message = "Unknown event received: " + eventId;
	}
	return message;
}

void EventsList::updateStatusManager(float deltaTime)
{
	statusManager->update(deltaTime);
}
}
