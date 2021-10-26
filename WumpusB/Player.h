/**************************************************
Project: Dragon Hunter
Assignment 2 (Major Project : A)
Author : Anthony Passarin
Purpose : Player class header file
* *************************************************/
#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <sstream>

#include "Location.h"

using namespace std;

class Player {
private:
	bool alive;
	int stamina;
	int coins;
	int arrows;
	string playerName;
	Location playerLoc;

public:
	//constructors
	Player();
	Player(string name);
	Player(string name, Location loc);
	~Player();

	//accessors
	string getName();
	Location getLoc();
	bool isAlive();

	//mutators
	void setStamina(int stamina);
	void setName(string name);
	void setLocation(Location loc);
	void setArrows(int amount);

	//methods
	int getStamina();
	int getArrows();
	int getCoins();
	string getPlayerDetails();
	void die();


};

#endif