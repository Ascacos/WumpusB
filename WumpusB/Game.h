/**************************************************
 Project: Dragon Hunter
 Assignment 2 (Major Project: A)
 Author: Anthony Passarin
 Purpose: Main program header file
**************************************************/
#ifndef GAME_H
#define GAME_H

#include <ctime>

using namespace std;

#include "Player.h"
#include "Location.h"
#include "Hazard.h"
#include "Wyvern.h"
#include "Dragon.h"
#include "Abyss.h"
#include "Util.h"
#include "Enums.h"
#include "Item.h"

// Create a Util object, so we can use 
// its utility functions
Util utils = Util();

void displayTitle();
void displayInfo();
void displayMap();
void displayLocation();
void displayIntro();

void setup();
void playGame();
void evaluateChoice(string choice, vector<string> exits);
void createLocations();
Player createPlayer();
void generateHazards();
void Death(DeathType type);
void displayExits();
void displayStats();
void mainMenu();
void selectDifficulty();
void shoot();
void save();
void load();
void checkHighscore(int score);
string getDifficulty();
void movePlayer(Location loc);
void moveDragon();
void generateItems();
//utility function to return the room (int) in direction (char NESW)
Location getRoom(char direction, vector<string> exits, Location currentLocation);
vector<Location> getNeighbours(Location loc);
Item* randomItem();

// Global variables


bool loaded = false;	//represents if the game has been loaded from a save or not
bool quit = false;		//if the player has quit
bool debug = false;		//if debug mode enabled
Difficulty difficulty;	//the game's difficulty
bool dragonAlive;		//is the dragon alive
Location dragonLoc;		//the location of the dragon
Player player;			// the player
vector<Location> map;	//a vector of locations, representing the game's map

#endif