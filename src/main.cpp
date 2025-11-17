#include <iostream>
#include <string>

#include "routine_manager.hpp"
#include "scheduler.hpp"

int main(int argc, char* argv[]) {
	std::string dataPath = "data/routines.json";
	if (argc < 2) {
		std::cout << "Usage:\n";
		std::cout << "  routine add\n";
		std::cout << "  routine start\n";
		return 0;
	}

	std::string cmd = argv[1];

	if (cmd == "add") {
		std::string id, time, name, desc;

		std::cout << "ID: ";
		std::getline(std::cin, id);

		std::cout << "Time (e.g., 6:30AM - 7:00AM): ";
		std::getline(std::cin, time);

		std::cout << "Name: ";
		std::getline(std::cin, name);

		std::cout << "Description: ";
		std::getline(std::cin, desc);

		RoutineManager rm(dataPath);
		rm.addTask(id, time, name, desc);

		std::cout << "Task added\n";
	} else if (cmd == "start") {
		Scheduler s(dataPath);
		s.run();
	}

	return 0;
}
