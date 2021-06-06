#pragma once
#include <vector>
#include "comparator.h"



namespace util { //namespace for anything that might be used twice, or really any function so we can get it away from the source/header files to keep it nice and clean

		//for the maps below, we might run into some problems with memory, but hopefully it shouldn't be *too* bad, we need the lookup speed to check if variable names already exist (ie, $var is a string, don't make a duplicate in int)


	using anyVar = std::variant<int, float, double, std::string>;
	bool search(std::string array[], int size, std::string target) //we do a little copy pasting
	{
		for (int i = 0; i < size; ++i)
		{
			if (array[i] == target)
			{
				return true;
			}
		}

		return false;
	}

	bool hasEnding(std::string const& fullString, std::string const& ending) { //thanks stackoverflow, now I don't have to do it myself
		if (fullString.length() >= ending.length()) {
			return (0 == fullString.compare(fullString.length() - ending.length(), ending.length(), ending));
		}
		else {
			return false;
		}
	}

	std::vector<std::string> split(std::string &str, std::string delimiter) {
		size_t pos = 0;
		std::string token;
		std::vector<std::string> result;
		while ((pos = str.find(delimiter)) != std::string::npos) {
			token = str.substr(0, pos);
			result.push_back(token);
			str = str.substr((size_t)pos + (size_t)delimiter.length());
		}
		result.push_back(str); //it just doesn't do the last one :(
		return result;
	}

	std::string getCommand(std::string &str) {
		return str.substr(0, str.find(" "));
	}

	std::string getTextInQuotes(std::string str) { //no reference :( we need the ability to pass through a substr, and it'll cost the same if we init a new string anyways
		return str.substr(str.find_first_of("\"")+1, str.find_last_of("\"")-1 - str.find_first_of("\""));
	}

	std::string getTextInP(std::string str) { //for parentheses
		return str.substr(str.find_first_of("(") + 1, str.find_last_of(")") - 1 - str.find_first_of("("));
	}




}