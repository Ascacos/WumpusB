/**************************************************
 Project: Dragon Hunter
 Assignment 2 (Major Project: A)
 Author: Anthony Passarin
 Purpose: Location header file
**************************************************/

#ifndef LOCATION_H
#define LOCATION_H

#include <string>
#include <sstream>
#include <vector>
//#include "Dragon.h"
#include "Hazard.h"
using namespace std;

class Location {
private:
	//attributes
	int locID;
	string locDesc;
	string locName;
	string locExits;
	Hazard* hazard;
	bool containsHazard;

public:
	//constructors
	Location();
	Location(string name, string desc, string exits);
	Location(string name, string desc, string exits, int id);
	//Location(string name, string desc, string exits, Hazard hazard)
	~Location();

	//accessors
	string getDescription();
	string getName();
	string getExits();
	Hazard* getHazard();
	bool hasHazard();
	int getID();

	//mutators
	void setDescription(string desc);
	void setName(string name);
	void setExits(string exits);
	void putHazard(Hazard* hazard);
	void killHazard();
	//methods
	string getLocationDetails();
	vector<string> getExitsVector();

};

#endif