/**************************************************
 Project: Dragon Hunter
 Assignment 2 (Major Project: A)
 Author: Anthony Passarin
 Purpose: Player class definition file
**************************************************/
#include "Player.h"

//constructors
Player::Player() {

	playerName = "";
}
Player::Player(string name) {
	score = 0;
	alive = true;
	coins = 0;
	arrows = 5;
	stamina = 20;
	playerName = name;
}
Player::Player(string name, int stam, int arr) {
	score = 0;
	alive = true;
	coins = 0;
	arrows = arr;
	stamina = stam;
	playerName = name;
}
Player::Player(string name, int stam, int arr, Location loc) {
	score = 0;
	alive = true;
	coins = 0;
	arrows = arr;
	stamina = stam;
	playerName = name;
	playerLoc = loc;
}
Player::~Player() {}

//accessors
string Player::getName() { return playerName; }
Location Player::getLoc() { return playerLoc; }
int Player::getStamina() { return stamina; }
int Player::getArrows() { return arrows; }
int Player::getCoins() { return coins; }
int Player::getScore() { return score; }
bool Player::isAlive() { return alive; }
bool Player::hasItem(ItemType type) {
	for (int i = 0; i < playerInventory.size(); i++) {
		if (playerInventory[i]->getType() == type) {
			return true;
		}
	}
	return false;
}
int Player::getItem(ItemType type) {
	for (int i = 0; i < playerInventory.size(); i++) {
		if (playerInventory[i]->getType() == type) {
			return i;
		}
	}
	return -1;
}

//mutators
void Player::setName(string name) { playerName = name; }
void Player::setLocation(Location loc) { playerLoc = loc; }
void Player::setArrows(int amount) { arrows = amount; }
void Player::setStamina(int amount) { stamina = amount; }
void Player::setScore(int amount) { score = amount; }
void Player::addScore(int amount) { score += amount; }
void Player::addItem(Item* item) {
	playerInventory.push_back(item);
}
void Player::removeItem(int index) {
	delete playerInventory[index];
	playerInventory[index] = nullptr;
	playerInventory.erase(playerInventory.begin() + index);
}
void Player::die() { alive = false; }

//methods
//display the player's inventory contents
string Player::showInventory()
{
	stringstream inventoryDetails;
	inventoryDetails << "\tYour inventory:\n";
	for (int i = 0; i < playerInventory.size(); i++) {
		inventoryDetails << i + 1 << ". " << playerInventory[i]->getName() << endl;
	}
	if (playerInventory.size() == 0) {
		cout << "\t...is empty" << endl;
	}

	inventoryDetails << "\n";

	// add other details here
	return inventoryDetails.str();
}




