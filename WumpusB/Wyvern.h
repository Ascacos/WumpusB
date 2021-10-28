#ifndef WYVERN_H
#define WYVERN_H

#include <vector>
#include "Hazard.h"
#include "Player.h"
#include "Location.h"
class Wyvern : public Hazard {

public:
	//constructors
	Wyvern();
	~Wyvern();

	//accessors
	int getNumWyverns();

	//public methods
	virtual void doAttack(Player& player, vector<Location>& map);
	void hint();
private:
	//static counter for wyverns
	static int numWyverns;

};

#endif