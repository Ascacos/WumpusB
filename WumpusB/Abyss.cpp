#include "Abyss.h"

//constructors
Abyss::Abyss() {
	name = "Abyss";
	type = HazardType::ABYSS;
}
Abyss::~Abyss() {}

//methods
//display the Abyss hint
void Abyss::hint() {
	cout << "\tYou hear a distinct echo, reflecting back at you from a nearby room." << endl;
}
//process functionality when player lands in an abyss
void Abyss::doAttack(Player& player) {

	cout << "\tYou fall into the abyss and die... What a pity!" << endl;

	// if the player has an escape rope in their inventory, 
	if (player.hasItem(ItemType::ESCAPE_ROPE)) {
		cout << "\tYou reach into your bag and grab the trusty Escape Rope you found earlier." << endl;
		cout << "\tThe Escape Rope has perished, but your life was spared..." << endl;
		
		// consume the escape rope
		player.removeItem(player.getItem(ItemType::ESCAPE_ROPE));
		system("pause");
		//return without killing the player
		return;
	}
	//if the player does not have an escape rope, kill the player
	else {
		player.die();
	}
}