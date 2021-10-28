#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class Util {
public:
	//constructor
	Util();

	//utility methods
	void dumpFile(string fileName);
	string askForString(string prompt);
	int askForNumber(string prompt, int min);
	char askForChar(string prompt);
	char askForChar(string prompt, string options);
	string tolower(string word);
	int getIntFromFile(string filename);
	void saveIntToFile(int value, string filename);
	bool isNumber(string str);
};

#endif