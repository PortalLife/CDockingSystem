#include <string>
#include <array>
#include "Port.h"

Berth::Berth()
{
//default constructor for arrays
}
Berth::Berth(ship_type capacity){
	this->capacity = capacity;
	this->dockedShip = nullptr;
}

