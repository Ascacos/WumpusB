#ifndef ABYSS_H
#define ABYSS_H

#include "Hazard.h"
#include "Player.h"
class Abyss : public Hazard {

public:
	//constructors
	Abyss();
	~Abyss();

	//public methods
	virtual void doAttack(Player& player);

private:
	//private methods
	void hint();
};

#endif