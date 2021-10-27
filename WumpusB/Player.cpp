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
/*
Player::Player(string name, Location loc) {
	alive = true;
	coins = 0;
	arrows = 5;
	stamina = 20;
	playerName = name;
	playerLoc = loc;
}*/

Player::~Player() {

}

//accessors
string Player::getName() { return playerName; }
Location Player::getLoc() { return playerLoc; }

void Player::setStamina(int amount) { stamina = amount; }

//mutators
void Player::setName(string name) { playerName = name; }
void Player::setLocation(Location loc) { playerLoc = loc; }

void Player::setArrows(int amount) { arrows = amount; }

void Player::setScore(int amount) { score = amount; }

void Player::addScore(int amount) { score += amount; }

int Player::getStamina() { return stamina; }
int Player::getArrows() { return arrows; }
//methods
string Player::getPlayerDetails() {
	stringstream playerDetails;
	playerDetails << "\tPlayer Profile:\n";
	playerDetails << "\n Name: " << playerName;
	playerDetails << "\n Location: " << playerLoc.getName();

	playerDetails << "\n";

	// add other details here
	return playerDetails.str();
}

void Player::die()
{
	alive = false;
}

bool Player::isAlive() {
	return alive;
}

int Player::getCoins() {
	return coins;
}

int Player::getScore() { return score; }
