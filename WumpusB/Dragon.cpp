#include "Dragon.h"

Dragon::Dragon() {
	name = "Dragon";
	type = HazardType::DRAGON;
	canMove = true;
}
Dragon::~Dragon() {}

void Dragon::doAttack() {
	cout << "\tYou wandered into the Dragon's den, and got gobbled up!" << endl;
}

void Dragon::hint()
{
	cout << "\tYou hear a low rumble from a nearby room." << endl;
}
