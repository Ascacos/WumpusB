#ifndef HAZARD_H
#define HAZARD_H

#include <string>
#include <iostream>
#include "Enums.h"
using namespace std;

class Hazard {
public:
	//constructors
	Hazard();
	~Hazard();

	//public methods
	virtual string getName();
	virtual void doAttack();
	virtual void hint() = 0;
	HazardType getType();
protected:
	//attributes
	HazardType type;
	string name;



};

#endif

