cmake_minimum_required(VERSION 3.16)
project(on-time-cli)

set(CMAKE_CXX_STANDARD 17)

find_package(nlohmann_json 3.2.0 REQUIRED)

add_executable(on_time
	src/main.cpp
	src/routine_manager.cpp
	src/notifier.cpp
	src/scheduler.cpp
)

target_link_libraries(on_time PRIVATE nlohmann_json::nlohmann_json)

target_include_directories(on_time PRIVATE include)
target_include_directories(on_time PRIVATE /usr/include)
