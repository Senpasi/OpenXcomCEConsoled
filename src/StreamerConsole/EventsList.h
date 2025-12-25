#pragma once
#include "StatusManager.h"
#include <string>
namespace OpenXcom
{
class EventsList
{
  private:
	StatusManager* statusManager;

  public:
	EventsList();
	std::string processEvent(const std::string& event);
	void updateStatusManager(float deltaTime);
};
}
