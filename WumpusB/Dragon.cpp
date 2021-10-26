#include "Dragon.h"

Dragon::Dragon() {
	name = "Dragon";
}
Dragon::~Dragon() {}

void Dragon::doAttack() {

	//check destination room for additional hazard
	cout << "Dragon attack" << endl;
}

void Dragon::hint()
{
	cout << "\tYou hear a low rumble from a nearby room." << endl;
}
