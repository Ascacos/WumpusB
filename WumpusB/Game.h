/**************************************************
 Project: Dragon Hunter
 Assignment 2 (Major Project: A)
 Author: Anthony Passarin
 Purpose: Main program header file
**************************************************/
#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <vector>
#include <stdlib.h>

#include <windows.h>

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

// 'print' functions
void displayTitle();
void displayInfo();
void displayMap();
void displayLocation();

// Core functions
void setup();
void playGame();
void evaluateChoice(char choice, vector<string> exits);
void createLocations();
Player createPlayer();
void generateHazards();
void Death(DeathType type);
void displayExits();
//adjacent room has hazard?

//utility function to return the room (int) in direction (char NESW)
Location getRoom(char direction, vector<string> exits, Location currentLocation);
vector<Location> getNeighbours(Location loc);


// Global variables
bool quit = false;
bool debug = false;
Player player;
vector<Location> map;

// to be implemented:
#endif