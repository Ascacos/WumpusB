#include "Wyvern.h"

//static wyvern counter
int Wyvern::numWyverns = 0;

//constructors
Wyvern::Wyvern() {
	name = "Wyvern";
	type = HazardType::WYVERN;

	numWyverns++;
}
Wyvern::~Wyvern() {
	numWyverns--;
}

//functionality for when a player lands on a wyvern
void Wyvern::doAttack(Player& player, vector<Location>& map) {
	cout << "\tYou encounter a Wyvern, and have been dropped in a random room." << endl;
	
	//find a random location from the map,
	int location = rand() % map.size();
	//and move the player there.
	player.setLocation(map[location]);
}

//display hint when in adjacent room
void Wyvern::hint() {
	cout << "\tYou hear the flapping of wings in a nearby room." << endl;
}

int Wyvern::getNumWyverns() {
	return numWyverns;
}