/**************************************************
 Project: Dragon Hunter
 Assignment 2 (Major Project: A)
 Author: Anthony Passarin
 Purpose: Location class definition file
**************************************************/

#include "Location.h"


//constructors
Location::Location() {
	locName = "Location";
	locDesc = "Description";
	locExits = "NSWE";
}

Location::Location(string name, string desc, string exits) {
	locName = name;
	locDesc = desc;
	locExits = exits;
	hazard = nullptr;
	containsHazard = false;
}

Location::Location(string name, string desc, string exits, int id) {
	locID = id;
	locName = name;
	locDesc = desc;
	locExits = exits;
	hazard = nullptr;
	containsHazard = false;
}

Location::Location(string name, string desc, string exits, int id, Hazard* haz) {
	locID = id;
	locName = name;
	locDesc = desc;
	locExits = exits;
	hazard = haz;
	containsHazard = true;
}
Location::~Location() { }

//accessors
string Location::getDescription() { return locDesc; }
string Location::getName() { return locName; }
string Location::getExits() { return locExits; }
Hazard* Location::getHazard() { return hazard; }
bool Location::hasHazard() { return containsHazard; }
int Location::getID() { return locID; }
//mutators
void Location::setDescription(string desc) { locDesc = desc; }
void Location::setName(string name) { locName = name; }
void Location::setExits(string exits) { locExits = exits; }
void Location::putHazard(Hazard* haz) {
	containsHazard = true;
	hazard = haz;
}

void Location::killHazard() {
	if (hasHazard()) {
		containsHazard = false;
		delete hazard;
		hazard = nullptr;

	}
	else {
		cout << "There's no hazard here..." << endl;
	}


}
//methods
string Location::getLocationDetails() {
	stringstream locationDetails;
	locationDetails << "\tLocation Profile:\n";
	locationDetails << "\n Name: " << locName;
	locationDetails << "\n Description: " << locDesc;
	locationDetails << "\n Exits: " << locExits;
	locationDetails << "\n";

	// add other details here in part B
	// (i.e. hazards)
	return locationDetails.str();
}

// Converts the exits string of a location to a vector,
// to make it easier to use in practice
vector<string> Location::getExitsVector() {
	vector<string> exitVector;
	istringstream ss(locExits);
	string token;
	while (getline(ss, token, ';')) {
		string exit;
		for (int i = 0; i < token.size(); i++) {
			exit += std::tolower(token[i]);
		}
		exitVector.push_back(exit);
	}


	return exitVector;
}
