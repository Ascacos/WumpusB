#ifndef DRAGON_H
#define DRAGON_H

#include "Hazard.h"
#include "Player.h"
class Dragon : public Hazard {

public:
	//constructors
	Dragon();
	~Dragon();

	//public methods
	virtual void doAttack(Player& player);
	void hint();
private:

};

#endif
