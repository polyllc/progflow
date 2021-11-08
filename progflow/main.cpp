#include <fstream>
#include <string>
#include "util.h"
#include "progflow.h"
#include "runCommands.h"
#include "variable.h"
#include "arithmetic.h"

void readFile(std::string filename);

int main(int argc, char** argv) {

	if (argc > 0) {
		//readFile(std::string(argv[1]));
		readFile("progflow.progflow");
	}
	else {
		std::cout << "\nInput a .progflow file in order to run it.\n";
	}
	return 0;
}

void readFile(std::string filename) {
	if (util::hasEnding(filename, ".progflow") == false) {
		std::cout << "\nInput a .progflow file, you entered a different type of file";
		exit(0);
	}
	std::fstream file(filename);
	if (file.is_open() == false) {
		std::cout << "\nCould not open " << filename << " for reading, check if you have access to the file or ProgFlow has access to it";
		exit(0);
	}
	//todo, read the file so it doesn't use a string (string are shit in c++ I hope I dont get a memory leak)
	std::string progflowProgram((std::istreambuf_iterator<char>(file)),
		std::istreambuf_iterator<char>()); //paste the file into a string, the best way to read a file!
	file.close(); //we don't need it anymore, ever

	while (progflowProgram.find('\t') != std::string::npos) {
		progflowProgram.erase(progflowProgram.find('\t'), 1); //remove all tabs so the program doesn't get confused 
	}

	std::vector<std::string> rawCommands = util::split(progflowProgram, "\n"); //split into a vector by newlines

	for (int i = 0; i < (int) rawCommands.size(); i++) { //remove all spaces from the beginning
		while (rawCommands[i].substr(0, 1) == " ") {
			rawCommands[i].erase(0, 1);
		}
	}

	progflow program(rawCommands);
	if (program.verifyCommands() == false) {
		std::cout << "\n\nResolve these issues before running again";
		exit(0);
	}
	std::cout << "Verified Commands!\n\n";

	util::runCommands(program.getCommands(), program);
	
	std::cout << "ProgFlow ran successfully! Press enter to quit.";
	std::string wedoalittlewaiting;
	std::getline(std::cin, wedoalittlewaiting);

}
