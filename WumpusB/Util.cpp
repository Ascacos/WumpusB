#include "Util.h"

Util::Util() {}


void Util::dumpFile(string fileName) {
	ifstream fileToRead(fileName);

	if (fileToRead.is_open()) {
		string line = "";
		while (!fileToRead.eof()) {
			getline(fileToRead, line);
			cout << line << "\n";
		}
	}
	else {
		cout << "\n" + fileName + " not found.\n";
	}
	fileToRead.close();
}

// Utility function to ask the user for a string input, with a prompt
string Util::askForString(string prompt) {
	string userInput;

	while (!userInput.length()) {
		cout << prompt;
		getline(cin, userInput);
	}

	return userInput;
}
// Utility function to ask the user for an integer input
// includes prompt and min
int Util::askForNumber(string prompt, int min) {

	int userInput = 0;

	while (userInput == 0) {
		cout << prompt;
		cin.clear();
		cin >> userInput;
	}

	return (userInput);
}
// Utility function to ask the user for a char input, with a prompt
char Util::askForChar(string prompt) {
	string userInput;

	while (!userInput.length() == 1) {
		cout << prompt;
		getline(cin, userInput);
	}

	return userInput[0];
}

string Util::tolower(string word) {
	string lower;
	for (char c : word) {
		lower += std::tolower(c);
	}
	return lower;
}