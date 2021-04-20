#pragma once
#include "util.h"
#include <unordered_map>
#include "command.h"
#include "variable.h"

std::string commandsString[] = {"print", "run", "loop", "if", "end", "store", "string", "int", "float", "double", "open"}; //viable commands that can be the first command (regexf and regexs can't be used standalone)



class progflow {
private:
	std::vector<std::string> commands;

	//for the maps below, we might run into some problems with memory, but hopefully it shouldn't be *too* bad, we need the lookup speed to check if variable names already exist (ie, $var is a string, don't make a duplicate in int)
	std::unordered_map<std::string, Variable<int>> intVariables;
	std::unordered_map<std::string, Variable<float>> floatVariables;
	std::unordered_map<std::string, Variable<double>> doubleVariables;
	std::unordered_map<std::string, Variable<std::string>> stringVariables;

public:
	progflow(std::vector<std::string> cmds) : commands(cmds) {}
	~progflow(){}

	bool verifyCommands(); //essentially, we check if the beginning of a line starts with a real command (or variable)
	bool processCommands();
	bool runCommands();
};

bool progflow::verifyCommands() {

	for (int i = 0; i < commands.size(); i++) {
		std::string command = util::getCommand(commands[i]); //the position of the space is also the length of the string that we need, neat!
		if (!util::search(commandsString, sizeof(commandsString) / sizeof(commandsString[0]), command)) {
			if (command.substr(0, 1) != "$" && command != "") { //meaning its also not a variable & skip all empty lines
				std::cout << "Unknown command \"" << command << "\". Make sure it's all in lowercase.";
				return false;
			}
		}
	}

	return true;
}

bool progflow::processCommands() {

	//todo, check the progflow to make sure everything is properly formatted
	return true;
}

bool progflow::runCommands() {
	for (int i = 0; i < commands.size(); i++) {
		std::string command = util::getCommand(commands[i]); //the position of the space is also the length of the string that we need, neat!
		if (command == "run") { //commence the if else galore! 
			Run run(util::getTextInQuotes(commands[i])); //removes the beginning " and the end " so commands with "s dont get screwed up
			//todo make sure to make it so it checks if the "s are there
			run.runCommand();
		}
	}
	return true;
}