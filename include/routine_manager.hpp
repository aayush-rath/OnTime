#pragma once
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

class RoutineManager {
public:
	RoutineManager(const std::string& path);

	nlohmann::json load();

	void save(const nlohmann::json& data);
	void addTask(
		const std::string& id,
		const std::string& time,
		const std::string& name,
		const std::string& description
	);

private:
	std::string filePath;
};
