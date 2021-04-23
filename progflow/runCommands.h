#pragma once
#include "util.h"
#include "command.h"

//we make an entire file just for this one function

namespace util {
	bool runCommands(std::vector<std::string>& commands) {
		for (int i = 0; i < (int) commands.size(); i++) {
			std::string command = util::getCommand(commands[i]); //the position of the space is also the length of the string that we need, neat!
			if (command == "run") { //commence the if else galore! 
				Run run(util::getTextInQuotes(commands[i])); //removes the beginning " and the end " so commands with "s dont get screwed up
				//todo make sure to make it so it checks if the "s are there
				run.runCommand();
			}

			if (command == "loop") {
				Loop loop();
			}

		}
		return false;
	}
}