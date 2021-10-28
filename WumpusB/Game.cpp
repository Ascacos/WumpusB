/**************************************************
 Project: Dragon Hunter
 Assignment 2 (Major Project: A)
 Author: Anthony Passarin
 Purpose: Main program file
**************************************************/

#include "Game.h"

int main() {
	//seed randoms
	srand((unsigned int)time(NULL));

	mainMenu();
	//display initial title

	//show about info & how to play
	if (!loaded) displayIntro();

	//get initial setup
	if (!loaded) setup();

	//do main game loop
	playGame();

	//wait before exitting
	system("pause");
}
//Do the pre-game menu
void mainMenu() {
	displayTitle();
	utils.dumpFile("menu.txt");

	int choice = utils.askForNumber("What would you like to do?: ", 0);
	switch (choice) {
	//play game
	case 1:
		break;
	//load a saved game
	case 2:
		load();
		system("pause");
		break;
	//change difficulty
	case 3:
		selectDifficulty();
		break;
	}
	system("cls");
}

//Select a difficulty
void selectDifficulty() {
	utils.dumpFile("difficulties.txt");
	
	int choice = utils.askForNumber("Select a difficulty: ", 0);
	switch (choice) {
	//Easy
	case 1:
		difficulty = Difficulty::EASY;
		cout << "\tDifficult set to easy." << endl;
		break;
	//Medium
	case 2:
		difficulty = Difficulty::MEDIUM;
		cout << "\tDifficult set to medium." << endl;
		break;
	//Hard
	case 3:
		difficulty = Difficulty::HARD;
		cout << "\tDifficult set to hard." << endl;
		break;
	default:
		cout << "Something went wrong..." << endl;
	}
	system("pause");
	system("cls");
	//return back to the main menu
	mainMenu();
}
//Initial setup of game environment
void setup() {
	displayTitle();

	//create player & ask for name (only if not loaded from file)
	if (!loaded) player = createPlayer();

	//generate location vectors from file
	createLocations();

	//initialise the player at location[0] --> the start!!
	player.setLocation(map[0]);

	//generate hazards
	generateHazards();

	//generate items
	generateItems();

	system("pause");
	system("cls");
}

void createLocations() {
	//fetch location names from file
	vector<string> locationNames;
	ifstream namesFile("locNames.txt");
	if (namesFile.is_open()) {
		string line = "";
		while (!namesFile.eof()) {
			getline(namesFile, line);
			locationNames.push_back(line);
		}
	}
	else {
		cout << "\n 'locNames.txt could not be found.\n";
	}
	namesFile.close();
	//fetch location descriptions from file
	vector<string> locationDescriptions;
	ifstream descFile("locDescriptions.txt");
	if (descFile.is_open()) {
		string line = "";
		while (!descFile.eof()) {
			getline(descFile, line);
			locationDescriptions.push_back(line);
		}
	}
	else {
		cout << "\n 'locDescriptions.txt could not be found.\n";
	}
	descFile.close();
	//fetch location exits from file
	vector<string> locationExits;
	ifstream exitsFile("locExits.txt");
	if (exitsFile.is_open()) {
		string line = "";
		while (!exitsFile.eof()) {
			getline(exitsFile, line);
			locationExits.push_back(line);
		}
	}
	else {
		cout << "\n 'locExits.txt' could not be found.\n";
	}
	exitsFile.close();
	//combine name, description, exits into vector<Location> map using location constructor
	//this relies on all files having identical line counts
	for (int i = 0; i < locationNames.size(); i++) {
		Location loc = Location(locationNames[i], locationDescriptions[i], locationExits[i], i);
		map.push_back(loc);
	}
}

// Function to create Player object, initialised with 
// a name given by the user
Player createPlayer() {
	cout << "\tFirst, please tell me your name!\n";

	cout.clear();
	cin.clear();
	string name = utils.askForString("\tEnter your name: ");
	Player player;
	
	//initialise the player's attributes (stamina & arrows) depending on difficulty chosen
	switch (difficulty) {
	case Difficulty::EASY:
		player = Player(name, 100, 10);
		break;
	case Difficulty::MEDIUM:
		player = Player(name, 50, 5);
		break;
	case Difficulty::HARD:
		player = Player(name, 20, 3);
		break;
	default: //default to easy difficulty
		player = Player(name, 100, 10);
		break;
	}
	// check if the user wants debug mode
	if (utils.tolower(name) == "tutor") { debug = true; }
	cout << "\tHi " << player.getName() << "! Good luck on your quest." << endl;
	return player;
}

// A simple function to print the game title
void displayTitle() {
	cout << "--------------------------------------------------------------------------------\n";
	cout << "\t\t\t\tDragon Hunter \n";
	cout << "--------------------------------------------------------------------------------\n";
}
void displayIntro() {
	displayTitle();
	utils.dumpFile("about.txt");
	utils.dumpFile("currencies.txt");
	system("pause");
	system("cls");
}
// A simple function to print the game menu, as part of the user interface
void displayMenu() {
	displayTitle();

	//display stats for the player
	cout << "\tStamina: " << player.getStamina()
		<< "\t\tArrows: " << player.getArrows()
		<< "\t\tScore: " << player.getScore()
		<< endl
		<< "\tDifficulty: " << getDifficulty() << endl;
	
	utils.dumpFile("compass.txt");
	cout << "--------------------------------------------------------------------------------\n";
}

// The core game loop
void playGame() {
	do {
		displayMenu();
		displayLocation();

		//check if room is hazard
		Location loc = player.getLoc();
		// check if the player's location has a hazard
		if (loc.hasHazard()) {
		//check what hazard is in the room
			if (loc.getHazard()->getType() == HazardType::DRAGON) {
				// process death by dragon
				Death(DeathType::DRAGON);
			}
			if (loc.getHazard()->getType() == HazardType::WYVERN) {

				Wyvern* wyvern = dynamic_cast<Wyvern*>(player.getLoc().getHazard());
				system("cls");
				displayTitle();
				//do main wyvern functionality (randomise player location)
				wyvern->doAttack(player, map);
				system("pause");
				system("cls");
				displayMenu();
				displayLocation();
			}
			if (loc.getHazard()->getType() == HazardType::ABYSS) {
				//process death by abyss
				Death(DeathType::ABYSS);
			}
		}

		if (player.getStamina() <= 0) {
			//if the player has a Stamina Bar, consume it and restore 5 stamina, saving them from death
			if (player.hasItem(ItemType::STAMINA_BAR)) {
				system("cls");
				displayTitle();
				cout << "\tYou ran out of stamina!" << endl << endl;
				cout << "\tThankfully, you have some spare Stamina Bars." << endl;
				cout << "\tYou take a moment to consume a Stamina Bar, restoring 5 Stamina." << endl;
				player.setStamina(player.getStamina() + 5);
				player.removeItem(player.getItem(ItemType::STAMINA_BAR));
				system("pause");
				system("cls");
				displayMenu();
				displayLocation();
			}
			//if the player does not have a Stamina Bar, process death by stamina
			else {
				Death(DeathType::STAMINA);
			}
		}
		// no arrows left, game over
		if (player.getArrows() <= 0) {
			Death(DeathType::ARROWS);
		}
		// check if the player is alive 
		if (player.isAlive()) {
			string userChoice;
			userChoice = utils.askForString("Enter an option: ");
			vector<string> exits = player.getLoc().getExitsVector();
			evaluateChoice(userChoice, exits);
		}
		system("cls");

		//check if the dragon is alive, if not, the player should win
		if (!dragonAlive) {
			displayTitle();
			cout << "\tYou killed the dragon!" << endl;
			displayStats();
			return;
		}	

	} while (!quit && player.isAlive());

	displayTitle();
	cout << "\tThank you for playing!" << endl;
	
	return;
}

//Process death by the various types
void Death(DeathType type) {
	Dragon* dragon = nullptr;
	Wyvern* wyvern = nullptr;
	Abyss* abyss = nullptr;
	system("cls");
	displayTitle();

	switch (type) {
	
	//death by abyss
	case DeathType::ABYSS: 
		abyss = dynamic_cast<Abyss*>(player.getLoc().getHazard());
		abyss->doAttack(player);
		if (player.isAlive()) {
			system("cls");
			displayMenu();
			displayLocation();
			//if the player is still alive, we want to return instead of break, to exit Death()
			return;
		}
		else break;
	//death by dragon
	case DeathType::DRAGON:
		dragon = dynamic_cast<Dragon*>(player.getLoc().getHazard());
		dragon->doAttack(player);
		break;
	//death by stamina
	case DeathType::STAMINA:
		cout << "You ran out of stamina and died." << endl;
		player.die();
		break;
	//death by arrows
	case DeathType::ARROWS:
		cout << "You ran out of arrows and will be unable to win!\n\tYou'll have to start over..." << endl;
		player.die();
		break;
	default:
		cout << "\tYou died!" << endl;
		player.die();
		break;
	}
	displayStats();
	system("pause");
	
}
// Display the player's final score at the end of the game
void displayStats() {
	cout << "\tYou got " << player.getScore() << " while exploring the caves." << endl;
	int staminaPoints = player.getStamina() * 10;	//10pts per stamina left
	int arrowPoints = player.getArrows() * 100;		//100pts per arrow left
	cout << "\tAdding " << staminaPoints << " for leftover stamina." << endl;
	cout << "\tAdding " << arrowPoints << " for leftover arrows." << endl;
	player.addScore(staminaPoints);				
	player.addScore(arrowPoints);				

	cout << "\n\tYour final score was: " << player.getScore() << endl;

	checkHighscore(player.getScore());
}

// Displays a formatted version of the player's current location
void displayLocation() {
	Location loc = player.getLoc();


	cout << "\t>> You enter " << loc.getName() << " ["<<loc.getID()<<"]"<< endl;
	cout << "\t>> " + loc.getDescription() << endl;
	cout << "\t>> You can see some exits, which way will you go?\n\n";

	displayExits();
	cout << "\n\n";

	//check neighbouring rooms for hazards (to display hint)
	vector<Location> neighbours = getNeighbours(player.getLoc());
	for (int i = 0; i < neighbours.size(); i++) {
		if (neighbours[i].hasHazard()) {
			Hazard* haz = neighbours[i].getHazard();
			haz->hint();
			if (debug) cout << "--" <<  haz->getName() << " in " << neighbours[i].getName() << endl;
		}
	}
	//check if the current location has an item
	if (loc.hasItem()) {
		cout << "\tYou found a " << loc.getItem()->getName() << endl;
		
		//add the item to the player's inventory
		player.addItem(new Item(loc.getItem()->getName(), loc.getItem()->getType()));
		// and remove it from the location
		map[loc.getID()].removeItem();
	}
}

// display the exits for the player's current location, formatted nicely
void displayExits() {
	vector<string> exits = player.getLoc().getExitsVector();
	for (int i = 0; i < exits.size(); i++) {
		cout << "\t\t[";
		cout << (char)std::toupper(exits[i][0]);
		cout << "]";

	}
}

// This function will evalutate the user's input during the core game loop
void evaluateChoice(string input, vector<string> exits) {

	if (input.size() == 1) {
		char choice;
		choice = tolower(input[0]);
		switch (choice) {
		case 'n':
			cout << "\tYou move North.\n";
			break;
		case 's':
			cout << "\tYou move South.\n";
			break;
		case 'w':
			cout << "\tYou move West.\n";
			break;
		case 'e':
			cout << "\tYou move East.\n";
			break;
		case 'q':
			quit = true;
			return;
		case 'm':
			displayMap();
			return;
		case 'i':
			displayInfo();
			return;
		default:
			cout << "Something went wrong...\n";
			return;
		}
		
		Location loc = getRoom(choice, exits, player.getLoc());
		
		// is the chosen direction a new room, or the same room?
		if (loc.getName() == player.getLoc().getName()) {

			//the player chose a direction that wasn't a valid exit
			cout << "\n\tBut there's nothing there... Try again!\n" << endl;
			system("pause");
			// return for the player to try again
			return;
		}

		// The direction was valid, so move the player
		movePlayer(loc);

		return;
	}

	//some other commands the player can select
	else {
		input = utils.tolower(input);
		if (input == "shoot") {
			shoot();
			return;
		}
		if (input == "save") {
			save();
			return;
		}
		//display the player's inventory
		if (input == "inventory") {
			system("cls");
			displayTitle();
		
			cout << player.showInventory() << endl;
			system("pause");
			return;
		}
	}
}

//move the player to a location
void movePlayer(Location loc) {
	player.setLocation(loc);
	player.setStamina(player.getStamina() - 1);
	moveDragon();
}

//determine if the dragon should move
void moveDragon() {
	int chance = rand() % 10;
	if (chance <= 1) {
		if (debug) cout << "-- Moving dragon, current loc: "
			<< dragonLoc.getName() << " "
			<< dragonLoc.getID() << endl;

		vector<Location> neighbours = getNeighbours(dragonLoc);
		int room = rand() % neighbours.size();
		map[dragonLoc.getID()].killHazard();
		map[neighbours[room].getID()].putHazard(new Dragon());
		dragonLoc = map[neighbours[room].getID()];
		if (debug) cout << "-- Moved dragon, new loc: "
			<< dragonLoc.getName() << " "
			<< dragonLoc.getID() << endl;
		cout << "\tThe Dragon has moved rooms." << endl;
		system("pause");
	}
}


void save() {
	ofstream file("save.txt");
	if (file.is_open()) {

		//save map, one location at a time
		file << "Saved file:" << endl;
		for (int i = 0; i < map.size(); i++) {
			file << "Location:" << endl;
			file << map[i].getID() << endl;
			file << map[i].getName() << endl;
			file << map[i].getDescription() << endl;
			file << map[i].getExits() << endl;
			if (map[i].hasHazard()) {
				Hazard* haz = map[i].getHazard();
				file << (int)haz->getType() << endl;
			}
			else {
				file << -1 << endl;
			}
			if (map[i].hasItem()) {
				Item* item = map[i].getItem();
				file << (int)item->getType() << endl;
			}
			else {
				file << -1 << endl;
			}

		}
		//save player saving here
		file << "Player:" << endl;
		file << player.getName() << endl;
		file << player.getScore() << endl;
		file << player.getStamina() << endl;
		file << player.getArrows() << endl;
		file << player.getLoc().getID() << endl;
	}
	else {
		cout << "File not found.\n\n";
	}

	file.close();
	cout << "\tGame has been saved. " << endl << endl;
	system("pause");

}
//load a game map from file
void load() {

	// open file for reading
	ifstream file("save.txt");
	map.clear();
	if (file.is_open()) {
		string line;
		getline(file, line);
	
		while (!file.eof()) {
			getline(file, line);
			if (line == "Location:") {
				int id;
				string name;
				string desc;
				string exits;

				cout << "\n\nLOCATION!!!" << endl;

				getline(file, line);
				cout << "Found id: " << line << endl;
				id = stoi(line);
				getline(file, line);
				cout << "Found name: " << line << endl;
				name = line;
				getline(file, line);
				cout << "Found desc: " << line << endl;
				desc = line;
				getline(file, line);
				cout << "Found exits: " << line << endl;
				exits = line;
				getline(file, line);

				cout << "Hazard: " << line << endl;

				switch (stoi(line)) {
				case -1:
					map.push_back(Location(name, desc, exits, id));
					break;
				case 0:
					map.push_back(Location(name, desc, exits, id, new Dragon()));
					dragonAlive = true;
					break;
				case 1:
					map.push_back(Location(name, desc, exits, id, new Wyvern()));
					break;
				case 2:
					map.push_back(Location(name, desc, exits, id, new Abyss()));
					break;
				default:
					break;
				}
				getline(file, line);
				switch (stoi(line)) {
				case -1:
					break;
				case 0:
					map[id].addItem(new Item("Stamina Bar", ItemType::STAMINA_BAR));
					break;
				case 1:
					map[id].addItem(new Item("Escape Rope", ItemType::ESCAPE_ROPE));
					break;
				default:
					break;
				}
				cout << "Map size: " << map.size() << endl;


			}

			if (line == "Player:"){
				cout << "Found playerdata" << endl;
				getline(file, line);
				player = Player(line);
				getline(file, line);
				player.setScore(stoi(line));
				getline(file, line);
				player.setStamina(stoi(line));
				getline(file, line);
				player.setArrows(stoi(line));
				getline(file, line);
				player.setLocation(map[stoi(line)]);
				//while (line != "inventory done") {
				//
				//}
			}
		}
	}
	else {
		cout << "\n Save file not found.\n";
	}
	// remember to close the file
	file.close();

	loaded = true;
}

void shoot() {
	char direction = utils.askForChar("What direction will you shoot your arrow?: ");
	Location target = getRoom(direction, player.getLoc().getExitsVector(), player.getLoc());

	// if the target room has a hazard,
	if (target.hasHazard()) {

		if (debug) cout << "--Shooting in room: " << target.getID() << " " << target.getName() << endl;
		if (debug) cout << "--Hazard: " << target.getHazard()->getName() << endl;

		Hazard* hazard = target.getHazard();
		switch (hazard->getType()) {
		
			//if the hazard is the dragon, kill the dragon
		case HazardType::DRAGON:
			//TODO: random chance to miss.
			map[target.getID()].killHazard();
			player.addScore(1000);
			dragonAlive = false;
			break;
			
			//if the hazard is a wyvern colony, kill the wyverns
		case HazardType::WYVERN:
			
			cout << "\n\tYou fire your arrow into a Wyvern colony!" << endl;
			cout << "\tThey didn't like it very much, and have dispersed " << endl;
			cout << "\tfurther into the adjacent corridors, leaving the cave empty." << endl;
			map[target.getID()].killHazard();
			player.addScore(250);
			break;

			//if the hazard is an abyss, do nothing
		case HazardType::ABYSS:
			cout << "You hear your arrow echo into the abyss." << endl;
			break;
		default:
			cout << "Something went wrong..." << endl;
			break;
		}

	}
	// if the is no hazard in the target room, do nothing
	else {
		cout << "You wasted an arrow!" << endl;
	}
	system("pause");
	//take 1 arrow from the player
	player.setArrows(player.getArrows() - 1);
}

// This function displays the 'stats' of the player
// to be fully implemented in part B
void displayInfo() {
	system("cls");
	displayTitle();
	utils.dumpFile("about.txt");
	utils.dumpFile("currencies.txt");
	cout << "--------------------------------------------------------------------------------\n";
	system("pause");
	system("cls");
	displayMenu();
}

// display the ASCII map, nicely
void displayMap() {
	system("cls");
	displayTitle();
	utils.dumpFile("map.txt");
	cout << "--------------------------------------------------------------------------------\n";
	system("pause");
	system("cls");
	displayMenu();
}

void generateHazards() {
	//generate Dragon first
	int Dragonloc = rand() % 5 + 15;

	//if the location already has a hazard, return (should never happen as this is generated first)
	if (map[Dragonloc].hasHazard()) {
		cout << "ERROR PLACING DRAGON!! Please restart your game." << endl;
		system("pause");
		return;
	}
	else {
		map[Dragonloc].putHazard(new Dragon());
		dragonLoc = map[Dragonloc];
		dragonAlive = true;
	}

	if (debug) cout << "--Dragon at: " << map[Dragonloc].getName() << " [" << map[Dragonloc].getID() << "]" << endl;

	//specify the max number of wyverns & abyss, based on the difficulty chosen
	int maxWyvern;
	int maxAbyss;
	switch (difficulty) {
	case Difficulty::EASY:
		maxWyvern = 2;
		maxAbyss = 2;
		break;
	case Difficulty::MEDIUM:
		maxWyvern = 3;
		maxAbyss = 3;
		break;
	case Difficulty::HARD:
		maxWyvern = 5;
		maxAbyss = 3;
		break;
	default:
		//default to easy
		maxWyvern = 2;
		maxAbyss = 2;
		break;
	}
	//counters
	int numWyverns = 0;
	int numAbyss = 0;

	while (numWyverns < maxWyvern) {
		int loc = rand() % 20;
		if (map[loc].hasHazard()) { continue; }
		else {
			(map[loc].putHazard(new Wyvern()));
			if (debug) cout << "--Wyvern at: " << map[loc].getName() << " " << map[loc].getID() << endl;
			numWyverns++;
		}

	}
	while (numAbyss < maxAbyss) {
		int loc = rand() % 20;
		if (map[loc].hasHazard()) { continue; }
		else {
			(map[loc].putHazard(new Abyss()));
			if (debug) cout << "--Abyss at: " << map[loc].getName() << " " << map[loc].getID() << endl;
			numAbyss++;
		}
	}
}

//randomly generate items around the map
void generateItems() {
	for (int i = 0; i < map.size(); i++) {
		
		//random number (0-99)
		int chance = rand() % 100;
		
		//~10% chance to create an item
		if (chance >= 90) {
			//check that the location doesnt have an item
			if (!map[i].hasItem()) {
				if (debug) cout << "--Adding item to " << map[i].getName() << " " << map[i].getID() << endl;
				//generate a random item, and place it in that location
				map[i].addItem(randomItem());
				if (debug) cout << "--Item is: " << map[i].getItem()->getName() << endl;
			}
			//if the location already has an item
			else {
				if (debug) cout << "--" << map[i].getName() << " already has item, skipping" << endl;
			}
		}
	}
	//always give the player 1 random item to start with.
	player.addItem(randomItem());
}

//function to generate a random item
Item* randomItem() {
	// random number (0 or 1)
	int item = rand() % 2;
	if (item == 0) {
		return new Item("Stamina Bar", ItemType::STAMINA_BAR);
	}
	if (item == 1) {
		return new Item("Escape Rope", ItemType::ESCAPE_ROPE);
	}
}

//return an adjacent Location, given the current location, exits, and chosen direction
Location getRoom(char direction, vector<string> exits, Location currentLocation) {
	for (int i = 0; i < exits.size(); i++) {				//loop over possible exits
		if (exits[i].find(direction) != string::npos) {		//if the user's direction exists in the list of exits
			string slice = exits[i].substr(1);
			Location loc = map[stoi(slice)];				//set the player's location to the index of the exit's location

			return loc;
		}
	}
	return currentLocation;
}
//return a vector of locations, representing the neighbours of a given location.
vector<Location> getNeighbours(Location loc) {
	vector<Location> neighbours;
	vector<string> exits = loc.getExitsVector();
	for (int i = 0; i < exits.size(); i++) {				//loop over possible exits															
		string slice = exits[i].substr(1);
		Location loc = map[stoi(slice)];				//set the player's location to the index of the exit's location

		neighbours.push_back(map[stoi(slice)]);
	}
	return neighbours;
}

//check if the current scores beats the highscore
void checkHighscore(int score) {
	int current = utils.getIntFromFile("highscore.txt");
	if (score > current) {
		utils.saveIntToFile(score, "highscore.txt");
	}
}

//return a string representation of the difficulty 
string getDifficulty() {
	switch (difficulty) {
	case Difficulty::EASY:
		return "Easy";
	case Difficulty::MEDIUM:
		return "Medium";
	case Difficulty::HARD:
		return "Hard";
	default:
		return "Easy";
	}
}