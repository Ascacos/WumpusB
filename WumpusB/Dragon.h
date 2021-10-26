#ifndef DRAGON_H
#define DRAGON_H

#include "Hazard.h"
#include "Player.h"
class Dragon : public Hazard {

public:
	Dragon();
	~Dragon();

	virtual void doAttack();
	void hint();
private:

};

#endif
