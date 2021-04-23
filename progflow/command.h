#pragma once
#include <iostream>
#include <vector>

enum Type {
	NONE, PRINT, RUN, STORE, OPEN, STRING, INT, FLOAT, DOUBLE, REGEXFIND, REGEXREPLACE, ASSIGNMENT //string, int, float and double are all types that are used at assign (i.e string $my_var = "hello world" we want that to be an explicit type so we don't get any problems (more work on the user not us))
};

class Command {
protected:
	Type commandType = NONE;
public:
	Command(){} 
	~Command(){}
};


class Run : Command{
private:
	std::string command;
public:
	Run(std::string cmd) : command(cmd) { commandType = RUN; }
	~Run() {}
	void runCommand();
};

void Run::runCommand() {
	int returnCode = system(command.c_str()); //we use system for compatibility, we use popen for the store command
	if (returnCode != 0) {
		std::cout << "\n\nCommand \"" << command << "\" did not return code 0. This maybe fine, but usually it means something else (return code: " << returnCode << ")\n\n";
	}
}




class Loop : Command {
private:
	std::vector<std::string> commands;
	std::string expression;
public:
	Loop(std::vector<std::string> commandVector, std::string exp) : commands(commandVector), expression(exp) {}
	~Loop() {}

};