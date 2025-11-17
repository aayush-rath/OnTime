#pragma once
#include <nlohmann/json.hpp>
#include <string>

class Scheduler {
public:
	Scheduler(const std::string& routinePath);
	void run();

private:
	std::string path;

	bool checkTimeMatch(const std::string& formatted, int hour, int minute);
	void parseTime(const std::string& timeRange,
			int& startHour, int& startMin,
			int& endHour, int& endMin);
};
