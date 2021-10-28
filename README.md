
	Dragon Hunter

Anthony Passarin
<student id>
apas0022@student.monash.edu

Assignment 3 for FIT1048 - Intro to C++
	
Game controls:
N/S/E/W to move in a direction.
'save' - will save the game at any time throughout a playthrough.
'shoot' - will prompt the user for a direction (make sure you press ENTER)
'inventory' - will show the player's inventory

===========================================
	Extra Functionality
===========================================

[X]	Debug mode - 'tutor'
	Mostly for ease of assessment for the assessor(s), you can enter 'debug' mode, by setting
	the player name as 'tutor', when prompted to input a name. This will provide some useful
	information about the location of hazards, and things that happen behind the scenes.
[2]	Difficulties
	The player can select a difficulty (Easy, Medium or Hard) before beginning a new game.
	This will affect the number of monsters generated, and the amount of stamina, and arrows 
	the player will start with.
[2] 	Scoring system
	There is a scoring system in place that adds an amount of points for killing Wyverns and
	the Dragon, and also adds extra points based on remaining stamina and arrows.
[2]	Wandering Wumpus (Dragon)
	The Dragon (Wumpus equivalent) has added functionality to move to an adjacent room, with
	a 30% chance. It IS possible for the Dragon to move into the room that the player is 
	occupying, but the player will not die. They can safely exit the room.
[3]	Themed Game
	The game is themed around medieval Dragon hunting, as opposed to the traditional Wumpus brief. 
	Bats are replaced with Wyverns, Pits replaced with Abyss, Wumpus replaced with Dragon.
	Instead of lamp oil, you simply have stamina (more fitting for a medieval RPG style adventure!)
	Arrows were kept, as they fit the theme well. All locations also have custom names and descriptions!
[4]	Load/Save functionality
	The game can be saved at any time by typing 'save' when prompted to enter a menu option (post-game
	start), and can be loaded from the main menu, when you first launch the program.
[6]	Items
	To keep things simple, only 2 items were added - the Escape Rope, and Stamina Bar.
	Escape Rope will save you if you fall into the Abyss (pit), and will be consumed on use.
	Stamina Bar's will be consumed when your stamina reaches 0, saving you from death. (+5 stamina)
	The player will always start with 1 (random) item, and a random number of items will be placed 
	throughout the game's locations. (use debug mode to see where they are at the start of your game)
[19] - marks
