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
	item = nullptr;
	containsItem = false;
}
Location::Location(string name, string desc, string exits, int id, Hazard* haz) {
	locID = id;
	locName = name;
	locDesc = desc;
	locExits = exits;
	hazard = haz;
	item = nullptr;
	containsHazard = true;
	containsItem = false;
}
Location::~Location() { }

//accessors
string Location::getDescription() { return locDesc; }
string Location::getName() { return locName; }
string Location::getExits() { return locExits; }
Hazard* Location::getHazard() { return hazard; }
bool Location::hasHazard() { return containsHazard; }
int Location::getID() { return locID; }
bool Location::hasItem() { return containsItem; }
Item* Location::getItem() { return item; }

//mutators
void Location::setDescription(string desc) { locDesc = desc; }
void Location::setName(string name) { locName = name; }
void Location::setExits(string exits) { locExits = exits; }
void Location::putHazard(Hazard* haz) {
	containsHazard = true;
	hazard = haz;
}
void Location::addItem(Item* i) { 
	item = i; 
	containsItem = true;
}
void Location::killHazard() {
	//double check that a hazard exists
	if (hasHazard()) {
		containsHazard = false;
		//delete pointer
		delete hazard;
		hazard = nullptr;
	}
	//if no hazard exists, do nothing
	else {
		cout << "There's no hazard here..." << endl;
	}


}
void Location::removeItem() {
	//double check that an item exists
	if (hasItem()) {
		containsItem = false;
		//delete pointer
		delete item;
		item = nullptr;
	}
	//if an item doesn't exist, do nothing
	else {
		cout << "There's no item here..." << endl;
	}
}

//methods
// Converts the exits string of a location to a vector,
// to make it easier to use in practice
vector<string> Location::getExitsVector() {
	vector<string> exitVector;
	istringstream ss(locExits);

	//this loop seperates the input string into a vector, seperated by ;
	//for example: N12;E14;S3 -> {N12, E14, S3}
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
