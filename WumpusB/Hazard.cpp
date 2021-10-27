#include "Hazard.h"

Hazard::Hazard() {
	name = "None";
	canMove = false;
}
Hazard::~Hazard() {}

string Hazard::getName() {
	return name;
}

HazardType Hazard::getType() {
	return type;
}

void Hazard::doAttack() {
	cout << "Hazard base" << endl;
}

void Hazard::hint()
{
}

