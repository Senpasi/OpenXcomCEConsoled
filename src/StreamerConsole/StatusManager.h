#pragma once
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include "../Engine/Yaml.h"

namespace OpenXcom
{

class Status
{
  public:
	virtual ~Status() = default;
	virtual void update(float deltaTime) = 0;
	virtual bool isExpired() const = 0;
    void setData(const YAML::YamlString& data) { _fullData = data; }
    const YAML::YamlString& getData() const { return _fullData; }
    bool hasData() const { return !_fullData.yaml.empty(); }
    YAML::YamlRootNodeReader getReader() const;
private:
    YAML::YamlString _fullData;
};

class TimeBasedStatus : public Status
{
  private:
	float duration;
	float elapsedTime;

  public:
	TimeBasedStatus(float duration);
	void update(float deltaTime) override;
	bool isExpired() const override;
	float getElapsedTime() const { return elapsedTime; }
	float getDuration() const { return duration; }
	float getRemainingTime() const { return duration - elapsedTime; }
};

class CounterBasedStatus : public Status
{
  private:
	int count;

  public:
	CounterBasedStatus(int count);
	void decrementCount();
	void addToCount(int amount);
	bool isExpired() const override;
	void update(float /*deltaTime*/) override;
};

class StatusManager
{
  private:
	using StatusPtr = std::unique_ptr<Status>;
	std::unordered_map<std::string, std::vector<StatusPtr>> statuses;

	// Singleton instance
	static StatusManager* instance;

	// Private constructor to prevent instantiation
	StatusManager() {}

  public:
	static StatusManager* getInstance();

	void addStatus(const std::string& identifier, StatusPtr status);
	bool hasStatus(const std::string& identifier) const;
	void removeStatus(const std::string& identifier);
	void update(float deltaTime);
	Status* getStatus(const std::string& identifier);
	std::vector<std::pair<std::string, Status*> > getStatusesByPrefix(const std::string& prefix) const;
	std::vector<std::string> getActiveIdentifiers() const;
};

}
