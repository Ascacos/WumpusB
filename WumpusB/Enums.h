/**************************************************
 Project: RPG World
 Lab Num: Week 6
 Author: Anthony Passarin
 Purpose: ENUMS Header definition File
**************************************************/
#ifndef ENUMS_H
#define ENUMS_H

enum class DeathType {
	ABYSS,
	WYVERN,
	DRAGON,
	STAMINA,
	ARROWS
};

enum class HazardType {
	DRAGON,
	WYVERN,
	ABYSS
};

enum class Difficulty {
	EASY,
	MEDIUM,
	HARD
};

#endif