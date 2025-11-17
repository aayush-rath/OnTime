#include "notifier.hpp"
#include <cstdlib>

void Notifier::send(const std::string& title, const std::string& msg) {
	std::string cmd = "notify-send '" + title + "' '" + msg +"'";
	system(cmd.c_str());
}

bool Notifier::askDone(const std::string& taskName) {
	std::string cmd = "zenity --question --text='Did you finish: "+taskName + "?'";

	int result = system(cmd.c_str());
	return result == 0;
}
