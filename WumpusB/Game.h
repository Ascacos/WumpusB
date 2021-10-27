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

// Utility functions
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

//utility function to return the room (int) in direction (char NESW)
Location getRoom(char direction, vector<string> exits, Location currentLocation);
vector<Location> getNeighbours(Location loc);

// Global variables
bool loaded = false;
bool quit = false;
bool debug = false;
Difficulty difficulty;
bool dragonAlive;
Player player;
vector<Location> map;

// to be implemented:
#endif