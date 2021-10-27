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
void mainMenu() {
	displayTitle();
	utils.dumpFile("menu.txt");

	int choice = utils.askForNumber("What would you like to do?: ", 0);
	switch (choice) {
	case 1:
		break;
	case 2:
		load();
		system("pause");
		break;
	case 3:
		selectDifficulty();
		break;
	}
	
	system("cls");
}
void selectDifficulty() {
	utils.dumpFile("difficulties.txt");
	
	int choice = utils.askForNumber("Select a difficulty: ", 0);
	switch (choice) {
	case 1:
		difficulty = Difficulty::EASY;
		cout << "\tDifficult set to easy." << endl;
		break;
	case 2:
		difficulty = Difficulty::MEDIUM;
		cout << "\tDifficult set to medium." << endl;
		break;
	case 3:
		difficulty = Difficulty::HARD;
		cout << "\tDifficult set to hard." << endl;
		break;
	default:
		cout << "Something went wrong..." << endl;
	}
	system("pause");
	system("cls");
	mainMenu();
}
void setup() {
	displayTitle();

	//create player & ask for name
	if (!loaded) player = createPlayer();

	//generate location vectors from file
	createLocations();

	//initialise the player at location[0] --> the start!!
	player.setLocation(map[0]);

	//generate hazards
	generateHazards();

	system("pause");
	//get more info from the user here
	// e.g. load saved game?
	//		change map theme?
	//		modify settings?
	//		(for full implementation)

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
	default:
		player = Player(name, 100, 10);
		break;
	}
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
	cout << "\tStamina: " << player.getStamina()
		<< "\t\tArrows: " << player.getArrows()
		<< "\t\tCoins: " << player.getCoins()
		<< endl
		<< "\tDifficulty: " << getDifficulty()
		<< "\t\tScore: " << player.getScore() << endl;
		
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
		if (loc.hasHazard()) {
			//check what hazard is in the room
			if (loc.getHazard()->getType() == HazardType::DRAGON) {
				Death(DeathType::DRAGON);
			}
			if (loc.getHazard()->getType() == HazardType::WYVERN) {
				Wyvern* wyvern = dynamic_cast<Wyvern*>(player.getLoc().getHazard());
				wyvern->doAttack(player, map);
				int location = rand() % map.size();
				player.setLocation(map[location]);
				system("pause");
				system("cls");
				displayMenu();
				displayLocation();
			}
			if (loc.getHazard()->getType() == HazardType::ABYSS) {
				Death(DeathType::ABYSS);
			}
		}

		if (player.getStamina() <= 0) {
			Death(DeathType::STAMINA);
		}
		if (player.getArrows() <= 0) {
			Death(DeathType::ARROWS);
		}
		if (player.isAlive()) {
			string userChoice;
			userChoice = utils.askForString("Enter an option: ");
			vector<string> exits = player.getLoc().getExitsVector();
			evaluateChoice(userChoice, exits);
		}
		system("cls");

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

void Death(DeathType type) {
	Dragon* dragon = nullptr;
	Wyvern* wyvern = nullptr;
	Abyss* abyss = nullptr;
	system("cls");
	displayTitle();
	//displayMenu();
	switch (type) {
	case DeathType::ABYSS: 
		abyss = dynamic_cast<Abyss*>(player.getLoc().getHazard());
		abyss->doAttack();
		break;
	case DeathType::DRAGON:
		dragon = dynamic_cast<Dragon*>(player.getLoc().getHazard());
		dragon->doAttack();
		break;
	case DeathType::STAMINA:
		cout << "You ran out of stamina and died." << endl;
		break;
	case DeathType::ARROWS:
		cout << "You ran out of arrows and will be unable to win!\n\tYou'll have to start over..." << endl;
		break;
	default:
		cout << "\tYou died!" << endl;
		break;
	}
	displayStats();
	system("pause");
	player.die();
}

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
	cout << "\t>> You enter " << loc.getName() << endl;
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

}
void displayExits() {
	vector<string> exits = player.getLoc().getExitsVector();
	for (int i = 0; i < exits.size(); i++) {
		cout << "\t\t[";
		cout << (char)std::toupper(exits[i][0]);
		cout << "]";
	}
}

// This function will evalutate the user's input
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
			//cout << "You choose Quit.\n";
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
		if (loc.getName() == player.getLoc().getName()) {
			cout << "\n\tBut there's nothing there... Try again!\n" << endl;
			system("pause");
			return;
		}
		player.setLocation(loc);
		player.setStamina(player.getStamina() - 1);
		return;
	}
	else {
		input = utils.tolower(input);
		if (input == "shoot") {
			shoot();
			return;
		}
		if (input == "save") {
			
			save();
			
			system("pause");
		}
	}
}

void save() {
	ofstream file("save.txt");
	if (file.is_open()) {

		//save map
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

}

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
			}
			//cout << " Last line for loc: " << line << endl;

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

	if (target.hasHazard()) {

		if (debug) cout << "--Shooting in room: " << target.getID() << " " << target.getName() << endl;
		if (debug) cout << "--Hazard: " << target.getHazard()->getName() << endl;

		Hazard* hazard = target.getHazard();
		switch (hazard->getType()) {
		case HazardType::DRAGON:
			//TODO: random chance to miss.
			map[target.getID()].killHazard();
			player.addScore(1000);
			dragonAlive = false;
			break;
		case HazardType::WYVERN:
			cout << "You fire your arrow into a Wyvern colony!" << endl;
			cout << "They didn't like it very much, and have dispersed " << endl;
			cout << "further into the adjacent corridors, leaving the cave empty." << endl;
			map[target.getID()].killHazard();
			player.addScore(250);
			break;
		case HazardType::ABYSS:
			cout << "You hear your arrow echo into the abyss." << endl;
			break;
		default:
			cout << "Something went wrong..." << endl;
			break;
		}

	}
	else {
		cout << "You wasted an arrow!" << endl;
	}
	system("pause");
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

	//if the location already has a hazard, return (should never happen is this is generated first)
	if (map[Dragonloc].hasHazard()) {
		cout << "ERROR PLACING DRAGON!! Please restart your game." << endl;
		system("pause");
		return;
	}
	else {
		map[Dragonloc].putHazard(new Dragon());
		dragonAlive = true;
	}

	if (debug) cout << "--Dragon at: " << map[Dragonloc].getName() << endl;


	//specify the max number of wyverns & abyss
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
			if (debug) cout << "--Wyvern at: " << map[loc].getName() << endl;
			numWyverns++;
		}

	}
	while (numAbyss < maxAbyss) {
		int loc = rand() % 20;
		if (map[loc].hasHazard()) { continue; }
		else {
			(map[loc].putHazard(new Abyss()));
			if (debug) cout << "--Abyss at: " << map[loc].getName() << endl;
			numAbyss++;
		}
	}
}

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

void checkHighscore(int score) {
	int current = utils.getIntFromFile("highscore.txt");
	if (score > current) {
		utils.saveIntToFile(score, "highscore.txt");
	}
}

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