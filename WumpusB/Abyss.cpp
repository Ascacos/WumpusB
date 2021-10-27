#include "Abyss.h"

Abyss::Abyss() {
	name = "Abyss";
	type = HazardType::ABYSS;
}
Abyss::~Abyss() {}

void Abyss::hint() {
	cout << "\tYou hear a distinct echo, reflecting back at you from a nearby room." << endl;
}
void Abyss::doAttack() {
	cout << "\tYou fall into the abyss and die... What a pity!" << endl;
}