#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class Util {
public:
	Util();

	void dumpFile(string fileName);
	string askForString(string prompt);
	int askForNumber(string prompt, int min);
	char askForChar(string prompt);
	string tolower(string word);
};

#endif