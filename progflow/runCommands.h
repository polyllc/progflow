#pragma once
#include "util.h"
#include "command.h"
#include "progflow.h"

//we make an entire file just for this one function
namespace util {

	Variable<anyVar> getVariable(progflow program, std::string var) {
		std::unordered_map<std::string, Variable<anyVar>>::const_iterator intMap = program.intVariables.find(var);
		std::unordered_map<std::string, Variable<anyVar>>::const_iterator strMap = program.stringVariables.find(var);
		std::unordered_map<std::string, Variable<anyVar>>::const_iterator floatMap = program.floatVariables.find(var);
		std::unordered_map<std::string, Variable<anyVar>>::const_iterator doubleMap = program.doubleVariables.find(var);
		if (intMap != program.intVariables.end()) {
			return Variable<anyVar>(intMap->second);
		}
		else if (strMap != program.stringVariables.end()) {
			return Variable<anyVar>(strMap->second);
		}
		else if (floatMap != program.floatVariables.end()) {
			return Variable<anyVar>(floatMap->second);
		}
		else if (doubleMap != program.doubleVariables.end()) {
			return Variable<anyVar>(doubleMap->second);
		}
		else {
			return Variable<anyVar>(NONE, 0);
		}
	}


		
	std::string replaceWithEscapeChars(std::string &str) {
		//std::cout << str.find("\\n");
		util::replaceAll(str, "\\n", "\n");
		util::replaceAll(str, "\\t", "\t");
		util::replaceAll(str, "\\r", "\r");
		util::replaceAll(str, "\\b", "\b");
		util::replaceAll(str, "\\f", "\f");
		return str;
	}

	std::string replaceWithVarString(progflow program, std::string str) { //todo update so $ in quotes do not replace, and make sure its in this format: $var + "wow" + $another_var
		std::string finalStr;
		if (str.find_first_of("$") != std::string::npos) {
			while (str.find_first_of("$") != std::string::npos) {
				finalStr += str.substr(0, str.find_first_of("$")); //get everything before the variable to replace
				str = str.substr(str.find_first_of("$")); //removes everything before the $

				int len = (str.find_first_of(" ") != std::string::npos ? str.substr(1, str.find_first_of(" ")).size()-1 : str.size()); //this is a great approach and will definitely not break

				Variable<anyVar> tempVar = getVariable(program, str.substr(1, len));
				if (tempVar.getType() != NONE) {
					switch (tempVar.getType()) {
					case INT: finalStr += std::to_string(std::get<int>(tempVar.readValue())); break;
					case STRING: finalStr += std::get<std::string>(tempVar.readValue()); break;
					case FLOAT: finalStr += std::to_string(std::get<float>(tempVar.readValue())); break;
					case DOUBLE: finalStr += std::to_string(std::get<double>(tempVar.readValue())); break;
					}
				}
				str = str.substr(str.substr(1, len+1).size());
			}
		}
		else {
			return str;
		}
		return finalStr + str; //make sure to add the rest of the str
	}
	std::string formatString(progflow program, std::string str) {
		std::string tempVarStr = replaceWithVarString(program, str);
		return replaceWithEscapeChars(tempVarStr);
	}

	void printOneByOne(std::string str) {
		for (int i = 0; i < str.size(); i++) {
			std::cout << str[i] << '\n';
		}
	}

	bool runCommands(std::vector<std::string> commands, progflow program) {
		for (int i = 0; i < (int) commands.size(); i++) {
			std::string command = util::getCommand(commands[i]); 
			if (command == "run") { //commence the if galore! 
				Run run(util::getTextInQuotes(commands[i])); //removes the beginning " and the end " so commands with "s dont get screwed up
				//todo make sure to make it so it checks if the "s are there
				run.runCommand();
			}

			if (command == "loop") {
				Loop loop();
			}

			if (command == "int") {
				std::string contents = commands[i].substr(command.size() + 2); //gets stuff after the command and the space following it
				std::string value = contents.substr(contents.find_first_of("=") + 1);
				int finalVal;
				std::string varname = contents.substr(0, contents.find_first_of(" "));
				try {
					finalVal = std::stoi(value);
				}
				catch (std::invalid_argument excep) {
					std::cout << "Value is not an integer when assigning to variable " << varname;
					exit(1);
				}

				if (getVariable(program, varname).getType() == NONE) {
					std::pair<std::string, Variable<anyVar>> var(varname, Variable<anyVar>(INT, finalVal)); //creates a new pair which is then inserted into the map
					program.intVariables.insert(var);
				}
				else {
					program.intVariables[varname] = Variable<anyVar>(INT, finalVal); //update variable at key
				}
			}

			if (command == "string") {
				std::string contents = commands[i].substr(command.size() + 2); //gets stuff after the command and the space following it
				std::string value = contents.substr(contents.find_first_of("=") + 2); //+2 to get rid of the space and the =
				std::string varname = contents.substr(0, contents.find_first_of(" "));
				
				if (getVariable(program, varname).getType() == NONE) {
					std::pair<std::string, Variable<anyVar>> var(varname, Variable<anyVar>(STRING, value)); //creates a new pair which is then inserted into the map
					program.stringVariables.insert(var);
				}
				else {
					program.stringVariables[varname] = Variable<anyVar>(STRING, value); //update variable at key
				}

			}

			if (command == "float") {
				std::string contents = commands[i].substr(command.size() + 2); //gets stuff after the command and the space following it
				std::string value = contents.substr(contents.find_first_of("=") + 1);
				float finalVal;
				std::string varname = contents.substr(0, contents.find_first_of(" "));
				try {
					finalVal = std::stof(value);
				}
				catch (std::invalid_argument excep) {
					std::cout << "Value is not an float when assigning to variable " << varname;
					exit(1);
				}

				if (getVariable(program, varname).getType() == NONE) {
					std::pair<std::string, Variable<anyVar>> var(varname, Variable<anyVar>(FLOAT, finalVal)); //creates a new pair which is then inserted into the map
					program.floatVariables.insert(var);
				}
				else {
					program.floatVariables[varname] = Variable<anyVar>(FLOAT, finalVal); //update variable at key
				}
			}

			if (command == "double") {
				std::string contents = commands[i].substr(command.size() + 2); //gets stuff after the command and the space following it
				std::string value = contents.substr(contents.find_first_of("=") + 1);
				double finalVal;
				std::string varname = contents.substr(0, contents.find_first_of(" "));
				try {
					finalVal = std::stod(value);
				}
				catch (std::invalid_argument excep) {
					std::cout << "Value is not an double when assigning to variable " << varname;
					exit(1);
				}

				if (getVariable(program, varname).getType() == NONE) {
					std::pair<std::string, Variable<anyVar>> var(varname, Variable<anyVar>(DOUBLE, finalVal)); //creates a new pair which is then inserted into the map
					program.doubleVariables.insert(var);
				}
				else {
					program.doubleVariables[varname] = Variable<anyVar>(DOUBLE, finalVal); //update variable at key
				}
			}


			if (command == "print") {
				std::cout << formatString(program, commands[i].substr(command.size() + 1));
			}

		}
		return false;
	}
}