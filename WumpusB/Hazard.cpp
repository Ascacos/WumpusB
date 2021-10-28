#include "Hazard.h"

//constructors
Hazard::Hazard() {}
Hazard::~Hazard() {}

//accessors
string Hazard::getName() { return name; }
HazardType Hazard::getType() { return type; }
//methods

//blank doAttack(), to be inherited by derived classes
void Hazard::doAttack(){}


