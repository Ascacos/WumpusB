/**************************************************
 Project: RPG World
 Lab Num: Week 6
 Author: Anthony Passarin
 Purpose: ENUMS Header definition File
**************************************************/
#ifndef ENUMS_H
#define ENUMS_H

//An enum to hold the possible death types
enum class DeathType {
	ABYSS,
	WYVERN,
	DRAGON,
	STAMINA,
	ARROWS
};

//An enum to hold the possible hazard types
enum class HazardType {
	DRAGON,
	WYVERN,
	ABYSS
};

//An enum to hold the possible difficulties
enum class Difficulty {
	EASY,
	MEDIUM,
	HARD
};

//An enum to hold the possible item types
enum class ItemType {
	STAMINA_BAR,
	ESCAPE_ROPE
};

#endif