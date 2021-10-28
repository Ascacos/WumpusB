
	Dragon Hunter

Assignment 3 for FIT1048 - Intro to C++
	
Game controls:
N/S/E/W to move in a direction.<br>
'save' - will save the game at any time throughout a playthrough.<br>
'shoot' - will prompt the user for a direction (make sure you press ENTER)<br>
'inventory' - will show the player's inventory<br>


	Extra Functionality

[X]	Debug mode - 'tutor'<br>
	Mostly for ease of assessment for the assessor(s), you can enter 'debug' mode, by setting<br>
	the player name as 'tutor', when prompted to input a name. This will provide some useful<br>
	information about the location of hazards, and things that happen behind the scenes.<br>
[2]	Difficulties<br>
	The player can select a difficulty (Easy, Medium or Hard) before beginning a new game.<br>
	This will affect the number of monsters generated, and the amount of stamina, and arrows <br>
	the player will start with.<br>
[2] 	Scoring system<br>
	There is a scoring system in place that adds an amount of points for killing Wyverns and<br>
	the Dragon, and also adds extra points based on remaining stamina and arrows.<br>
[2]	Wandering Wumpus (Dragon)<br>
	The Dragon (Wumpus equivalent) has added functionality to move to an adjacent room, with<br>
	a 30% chance. It IS possible for the Dragon to move into the room that the player is <br>
	occupying, but the player will not die. They can safely exit the room.<br>
[3]	Themed Game<br>
	The game is themed around medieval Dragon hunting, as opposed to the traditional Wumpus brief. <br>
	Bats are replaced with Wyverns, Pits replaced with Abyss, Wumpus replaced with Dragon.<br>
	Instead of lamp oil, you simply have stamina (more fitting for a medieval RPG style adventure!)<br>
	Arrows were kept, as they fit the theme well. All locations also have custom names and descriptions!<br>
[4]	Load/Save functionality<br>
	The game can be saved at any time by typing 'save' when prompted to enter a menu option (post-game<br>
	start), and can be loaded from the main menu, when you first launch the program.<br>
[6]	Items<br>
	To keep things simple, only 2 items were added - the Escape Rope, and Stamina Bar.<br>
	Escape Rope will save you if you fall into the Abyss (pit), and will be consumed on use.<br>
	Stamina Bar's will be consumed when your stamina reaches 0, saving you from death. (+5 stamina)<br>
	The player will always start with 1 (random) item, and a random number of items will be placed <br>
	throughout the game's locations. (use debug mode to see where they are at the start of your game)<br>
[19] - marks<br>
