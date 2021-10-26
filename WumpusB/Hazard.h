#ifndef HAZARD_H
#define HAZARD_H

#include <string>
#include <iostream>

using namespace std;

class Hazard {
public:
	//constructors
	Hazard();
	~Hazard();

	//public methods
	virtual string getName();
	virtual void doAttack();
	virtual void hint();
protected:
	//attributes
	string name;
	bool canMove;



};

#endif

