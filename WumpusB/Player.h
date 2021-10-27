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
	int score;
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
	Player(string name, int stamina, int arrows);
	Player(string name, int stamina, int arrows, Location loc);
	~Player();

	//accessors
	int getStamina();
	int getArrows();
	int getCoins();
	int getScore();
	string getName();
	Location getLoc();
	bool isAlive();

	//mutators
	void setStamina(int stamina);
	void setName(string name);
	void setLocation(Location loc);
	void setArrows(int amount);
	void setScore(int amount);
	void addScore(int amount);

	//methods

	
	string getPlayerDetails();
	void die();


};

#endif