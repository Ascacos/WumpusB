#include "Item.h"

//constructors
Item::Item() {
	name = "Item";
}
Item::Item(string n, ItemType t) {
	name = n;
	type = t;
}
Item::~Item() {}

//accessors
string Item::getName() {
	return name;
}
ItemType Item::getType() {
	return type;
}

//mutators
void Item::setName(string n) {
	name = n;
}
void Item::setType(ItemType t) {
	type = t;
}