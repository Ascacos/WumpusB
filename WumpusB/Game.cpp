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

	//display initial title
	displayTitle();

	//main menu

	//show about info & how to play
	utils.dumpFile("about.txt");
	system("pause");
	system("cls");
	//get initial setup

	setup();


	//test player
	//test();

	//do main game loop
	playGame();

	//wait before exitting
	system("pause");
}

void setup() {
	displayTitle();

	cout << "\tFirst, please tell me your name!\n";

	//create player & ask for name

	player = createPlayer();
	cout << "\tHi " << player.getName() << "! Good luck on your quest." << endl;

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
		Location loc = Location(locationNames[i], locationDescriptions[i], locationExits[i]);
		map.push_back(loc);
	}
}

// Function to create Player object, initialised with 
// a name given by the user
Player createPlayer() {
	cout << "\t";
	string name = utils.askForString("Enter your name: ");
	Player player = Player(name);
	if (utils.tolower(name) == "tutor") { debug = true; }
	return player;
}

// A simple function to print the game title
void displayTitle() {
	cout << "--------------------------------------------------------------------------------\n";
	cout << "\t\t\t\tDragon Hunter \n";
	cout << "--------------------------------------------------------------------------------\n";
}

// A simple function to print the game menu, as part of the user interface
void displayMenu() {
	displayTitle();
	cout << "\tStamina: " << player.getStamina()
		<< "\t\tArrows: " << player.getArrows()
		<< "\t\tCoins: " << player.getCoins() << endl;
	utils.dumpFile("compass.txt");
	cout << "--------------------------------------------------------------------------------\n";
}

// The core game loop
void playGame() {
	// initialise hazard pointers
	// putting them here ensures I can delete them after the core do-while loop
	Dragon* dragon = nullptr;
	Wyvern* wyvern = nullptr;
	Abyss* abyss = nullptr;
	do {
		displayMenu();
		displayLocation();

		//check if room is hazard
		Location loc = player.getLoc();
		if (loc.hasHazard()) {
			if (loc.getHazard()->getName() == "Dragon")
			{
				Dragon* dragon = dynamic_cast<Dragon*>(loc.getHazard());

				dragon->doAttack();
				Death(DRAGON);
			}
			if (loc.getHazard()->getName() == "Wyvern")
			{
				//system("cls");
				//displayMenu();

				cout << "\tYou encounter a Wyvern, and have been dropped in a random room." << endl;

				Wyvern* wyvern = dynamic_cast<Wyvern*>(loc.getHazard());
				wyvern->doAttack(player, map);
				int location = rand() % map.size();
				player.setLocation(map[location]);

				system("pause");
				system("cls");

				playGame();
			}
			if (loc.getHazard()->getName() == "Abyss") {
				Death(ABYSS);
			}
		}

		if (player.getStamina() <= 0) {
			Death(STAMINA);
		}
		if (player.getArrows() <= 0) {
			Death(ARROWS);
		}

		if (player.isAlive()) {
			char userChoice;
			userChoice = utils.askForChar("Enter an option: ");
			vector<string> exits = player.getLoc().getExitsVector();
			evaluateChoice(userChoice, exits);
		}

		system("cls");

	} while (!quit && player.isAlive());

	// GameOver();

	system("cls");
	displayMenu();

	cout << "Game over!" << endl;
}

void Death(DeathType type) {
	switch (type) {
	case ABYSS: 
		cout << "Death by abyss" << endl;
		break;
	case WYVERN: 
		cout << "Death by wyvern" << endl;
		break;
	case DRAGON:
		cout << "Death by dragon" << endl;
		break;
	case STAMINA:
		cout << "You ran out of stamina and died." << endl;
		break;
	case ARROWS: 
		cout << "You ran out of arrows and will be unable to win!" << endl;
		break;
	default:
		cout << "Somethin went wrong..." << endl;
		break;
	}
	system("pause");
	displayMenu();
	cout << "ABYSS!!" << endl;
	player.die();
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
			if (debug) cout << haz->getName() << " in " << neighbours[i].getName() << endl;
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
void evaluateChoice(char choice, vector<string> exits) {
	choice = tolower(choice);
	switch (choice) {
	case 'N':
	case 'n':
		cout << "\tYou move North.\n";
		break;
	case 'S':
	case 's':
		cout << "\tYou move South.\n";
		break;
	case 'W':
	case 'w':
		cout << "\tYou move West.\n";
		break;
	case 'E':
	case 'e':
		cout << "\tYou move East.\n";
		break;
	case 'Q':
	case 'q':
		//cout << "You choose Quit.\n";
		quit = true;
		return;
	case 'M':
	case 'm':
		displayMap();
		return;
	case 'I':
	case 'i':
		displayInfo();
		return;
	case 'G':
	case 'g':
		cout << "Shoot" << endl;
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
		return;
	}
	else map[Dragonloc].putHazard(new Dragon());

	if (debug) cout << "Dragon at: " << map[Dragonloc].getName() << endl;


	//specify the max number of wyverns & abyss
	int maxWyverns = 2;
	int maxAbyss = 2;

	//counters
	int numWyverns = 0;
	int numAbyss = 0;

	while (numWyverns < maxWyverns) {
		int loc = rand() % 20;
		if (map[loc].hasHazard()) { continue; }
		else {
			(map[loc].putHazard(new Wyvern()));
			if (debug) cout << "Wyvern at: " << map[loc].getName() << endl;
			numWyverns++;
		}

	}
	while (numAbyss < maxAbyss) {
		int loc = rand() % 20;
		if (map[loc].hasHazard()) { continue; }
		else {
			(map[loc].putHazard(new Abyss()));
			if (debug) cout << "Abyss at: " << map[loc].getName() << endl;
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
