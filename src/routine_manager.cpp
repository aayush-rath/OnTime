#include "routine_manager.hpp"
#include <fstream>
#include <iostream>

using json = nlohmann::json;

RoutineManager::RoutineManager(const std::string& path) : filePath(path) {}

json RoutineManager::load() {
	std::ifstream file(filePath);
	if (!file.is_open()) {
		return json::array();
	}

	json data;
	file >> data;
	return data;
}

void RoutineManager::save(const json& data) {
	std::ofstream file(filePath);
	file << data.dump(4);
}

void RoutineManager::addTask(
	const std::string& id,
	const std::string& time, 
	const std::string& name,
	const std::string& description
) {
	json data = load();

	json newTask;
	newTask["id"] = id;
	newTask["time"] = time;
	newTask["name"] = name;
	newTask["description"] = description;

	data.push_back(newTask);
	save(data);
}
