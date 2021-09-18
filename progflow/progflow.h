#pragma once
#include "util.h"
#include <unordered_map>
#include "command.h"
#include "variable.h"

std::string commandsString[] = {"print", "run", "loop", "if", "end", "store", "input", "string", "int", "float", "double", "open", "cast", "write", "program"}; //viable commands that can be the first command (regexf and regexs can't be used standalone)
//i might just make an auto cast later down the line




class progflow {
private:
	std::vector<std::string> commands;


public:
	progflow(std::vector<std::string> cmds) : commands(cmds) {}
	~progflow(){}

	bool verifyCommands(); //essentially, we check if the beginning of a line starts with a real command (or variable)
	bool processCommands();
	bool run();
	std::vector<std::string> getCommands();

	std::unordered_map<std::string, Variable<anyVar>> intVariables;
	std::unordered_map<std::string, Variable<anyVar>> floatVariables;
	std::unordered_map<std::string, Variable<anyVar>> doubleVariables;
	std::unordered_map<std::string, Variable<anyVar>> stringVariables;

};

bool progflow::verifyCommands() {
	bool verified = true;
	for (int i = 0; i < (int) commands.size(); i++) {
		std::string command = util::getCommand(commands[i]); //the position of the space is also the length of the string that we need, neat!
		if (!util::search(commandsString, sizeof(commandsString) / sizeof(commandsString[0]), command)) {
			if (command.substr(0, 1) != "$" && command != "" && command.substr(0, 2) != "//") { //meaning its also not a variable & skip all empty lines
				std::cout << "Unknown command \"" << command << "\". Make sure it's all in lowercase.\n";
				verified = false;
			}
		}
		if (command == "int" || command == "string" || command == "float" || command == "double") {
			if (commands[i].substr(command.size() + 1).substr(0, 1) != "$") {
				std::cout << "Invalid variable, add a $ before any variable (line was " << commands[i] << " , maybe try making it " << command << " $" << commands[i].substr(command.size() + 1) << "?)\n";
				verified = false;
			}
		}
	}

	return verified;
}

bool progflow::processCommands() {

	//todo, check the progflow to make sure everything is properly formatted
	return true;
}

std::vector<std::string> progflow::getCommands() {
	return commands;
}
