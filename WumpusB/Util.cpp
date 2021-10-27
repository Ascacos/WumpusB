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
	cout << flush;
	while (!userInput.length()) {
		cout << '\n' <<prompt;
		//cin.ignore(1, '\n'); // To fix double-firing of cout
		getline(cin, userInput);
	}

	return userInput;
}
// Utility function to ask the user for an integer input
// includes prompt and min
int Util::askForNumber(string prompt, int min) {
	double userInput = -1;
	bool valid = false;
	do
	{
		cout << prompt;
		cin >> userInput;
		if (cin.good())
		{
			if (userInput > min) {
				valid = true;
			}
			else {
				valid = false;
			}
			valid = true;
		}

		else
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input, try again!" << endl;
		}
	} while (!valid);

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

char Util::askForChar(string prompt, string options) {
	// ask a single letter response question
	char choice = ' ';
	while (choice == ' ') {
		cout << " " << prompt;
		cin >> choice;
		if (options.find(choice) == string::npos) {
			// the input letter is not a valid response
			choice = ' ';
		}
		cout << endl;
	}
	// convert to UPPERCASE
	return toupper(choice);
}

string Util::tolower(string word) {
	string lower;
	for (char c : word) {
		lower += std::tolower(c);
	}
	return lower;
}

int Util::getIntFromFile(string filename) {
	// open file for reading
	ifstream file(filename);
	string line;
	if (file.is_open()) {
		getline(file, line);
	}
	else {
		cout << filename << " not found." << endl;
	}
	// remember to close the file
	file.close();

	if (isNumber(line) && !line.empty()) {
		return (stoi(line));
	}
	else {
		cout << "Failed to cast highscore to int." << endl;
		return -1;
	}
}

void Util::saveIntToFile(int value, string filename) {
	ofstream file("highscore.txt");
	if (file.is_open()) {
		file << value;
		cout << "Saved new highscore" << endl;
	}
	else {
		cout << filename << " not found." << endl;
	}
	file.close();
}

bool Util::isNumber(string str)
{
	for (char c : str) {
		if (!isdigit(c)) return false;
	}
	return true;
}
