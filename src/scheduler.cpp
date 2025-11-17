#include "scheduler.hpp"
#include "routine_manager.hpp"
#include "notifier.hpp"

#include <chrono>
#include <thread>
#include <iostream>

using json = nlohmann::json;

Scheduler::Scheduler(const std::string& routinePath) : path(routinePath) {};

void Scheduler::parseTime(const std::string& range,
				int& sh, int& eh,
				int& sm, int& em)
{
	auto sep = range.find(" - ");
	std::string start = range.substr(0, sep);
	std::string end = range.substr(sep + 3);

	auto parseOne = [](const std::string& t, int& h, int& m) {
		sscanf(t.c_str(), "%d:%d", &h, &m);
		bool isPM = t.find("PM") != std::string::npos;
		if (isPM && h < 12) h += 12;
		if (!isPM && h == 12) h = 0;
	};

	parseOne(start, sh, sm);
	parseOne(end, eh, em);
}

bool Scheduler::checkTimeMatch(const std::string& t, int h, int m) {
	int th, tm;
	bool isPM = t.find("PM") != std::string::npos;
	sscanf(t.c_str(), "%d:%d", &th, &tm);

	if (isPM && th < 12) th += 12;
	if (!isPM && th == 12) th = 0;

	return th == h && tm == m;
}

void Scheduler::run() {
	RoutineManager rm(path);
	while(true) {
		json tasks = rm.load();

		auto now = std::chrono::system_clock::now();
		time_t t = std::chrono::system_clock::to_time_t(now);

		tm* lt = localtime(&t);

		int hour = lt->tm_hour;
		int minute = lt->tm_min;

		for (auto& task : tasks) {
			std::string range = task["time"];
			int sh, sm, eh, em;

			parseTime(range, sh, sm, eh, em);

			if (hour == sh && minute == sm) {
				Notifier::send("Task Started", task["name"]);
			}

			if (hour == eh && minute == em) {
				bool done = Notifier::askDone(task["name"]);
				if (!done) {
					Notifier::send("Reminder", "Please finish: " + std::string(task["name"]));
				}
			}
		}
		std::this_thread::sleep_for(std::chrono::minutes(1));
	}
}
