#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <iostream>
#include "Enums.h"
using namespace std;

class Item {
public:
	//constructors
	Item();
	Item(string name, ItemType type);
	~Item();

	//accessors
	string getName();
	ItemType getType();

	//mutators
	void setName(string n);
	void setType(ItemType t);
private:
	//attributes
	string name;
	ItemType type;
};

#endif