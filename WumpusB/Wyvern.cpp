#include "Wyvern.h"

Wyvern::Wyvern() {
	name = "Wyvern";
}
Wyvern::~Wyvern() {}

void Wyvern::doAttack(Player player, vector<Location> map) {
	//check destination room for additional hazard
	cout << "Wyvern attack" << endl;
}

void Wyvern::hint() {
	cout << "\tYou hear the flapping of wings in a nearby room." << endl;
}