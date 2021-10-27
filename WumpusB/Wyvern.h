#ifndef WYVERN_H
#define WYVERN_H

#include <vector>
#include "Hazard.h"
#include "Player.h"
#include "Location.h"
class Wyvern : public Hazard {

public:
	Wyvern();
	~Wyvern();

	virtual void doAttack(Player player, vector<Location> map);
	void hint();
	int getNumWyverns();
private:
	static int numWyverns;

};

#endif