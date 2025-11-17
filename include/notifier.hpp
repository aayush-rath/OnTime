#pragma once
#include <string>

class Notifier{
public:
	static void send(const std::string& title, const std::string& msg);
	static bool askDone(const std::string& taskName);
};
