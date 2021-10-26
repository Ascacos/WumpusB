#ifndef ABYSS_H
#define ABYSS_H

#include "Hazard.h"

class Abyss : public Hazard {

public:
	Abyss();
	~Abyss();

	virtual void doAttack();

private:
	void hint();
};

#endif