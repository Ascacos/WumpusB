#include "Dragon.h"

//constructors
Dragon::Dragon() {
	name = "Dragon";
	type = HazardType::DRAGON;
}
Dragon::~Dragon() {}

//process functionality when the player lands on a Dragon
void Dragon::doAttack(Player& player) {
	cout << "\tYou wandered into the Dragon's den, and got gobbled up!" << endl;
	player.die();
}

//display Dragon hint when in adjacent room
void Dragon::hint() {
	cout << "\tYou hear a low rumble from a nearby room." << endl;
}
