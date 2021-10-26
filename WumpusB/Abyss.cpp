#include "Abyss.h"

Abyss::Abyss() {
	name = "Abyss";
}
Abyss::~Abyss() {}

void Abyss::hint() {
	cout << "\tYou hear a distinct echo, reflecting back at you from a nearby room." << endl;
}
void Abyss::doAttack() {
	cout << "Abyss attack" << endl;
}