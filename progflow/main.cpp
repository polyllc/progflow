#include <fstream>
#include <string>
#include "util.h"
#include "progflow.h"
#include "runCommands.h"

void readFile(std::string filename);

int main(int argc, char** argv) {

	util::comparatorExpression thing(Variable<util::anyVar>(INT, 69), Variable<util::anyVar>(INT, 69), util::EQUAL);
	util::comparatorExpression things(Variable<util::anyVar>(INT, "122"), Variable<util::anyVar>(INT, "12"), util::NOTEQUAL);

	util::comparatorExpression thing2(true, thing, things, util::AND); //fix
	//std::cout << thing.evaluate();  //equal to ("hello" != "hello") || ("hello" != "hello")
	std::cout << "thing2\n\n";
	std::cout << (thing2.evaluate()); //("hello" != "hello") && ("122" != "12")
	std::cout << "\n\nthing2 thing2\n\n";
	util::comparatorExpression thing3(true, thing2, thing2, util::AND);
	std::cout << thing2.evaluate() && thing2.evaluate();  //equal to (("hello" != "hello") && ("122" != "12")) && (("hello" != "hello") && ("122" != "12"))
	std::cout << "\n\nthing3\n\n";
	std::cout << (thing3.evaluate());

	

	if (argc > 0) {
		//readFile(std::string(argv[1]));
		readFile("test.progflow");
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

	program.runCommands();

	std::cout << "ProgFlow ran successfully! Press enter to quit.";
	std::string wedoalittlewaiting;
	std::getline(std::cin, wedoalittlewaiting);

}