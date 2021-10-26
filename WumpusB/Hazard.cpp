#include "Hazard.h"

Hazard::Hazard() {
	name = "None";
	canMove = false;
}
Hazard::~Hazard() {}

string Hazard::getName() {
	return name;
}

void Hazard::doAttack() {
	cout << "Hazard base" << endl;
}

void Hazard::hint()
{
}

