#include "Wyvern.h"

int Wyvern::numWyverns = 0;

Wyvern::Wyvern() {
	name = "Wyvern";
	type = HazardType::WYVERN;
	numWyverns++;
}
Wyvern::~Wyvern() {
	numWyverns--;
}

void Wyvern::doAttack(Player player, vector<Location> map) {
	cout << "\tYou encounter a Wyvern, and have been dropped in a random room." << endl;	
}

void Wyvern::hint() {
	cout << "\tYou hear the flapping of wings in a nearby room." << endl;
}

int Wyvern::getNumWyverns() {
	return numWyverns;
}