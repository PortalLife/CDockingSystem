#include "Port.h"

Ship::Ship()
{
	// this has to be here because of arrays - complier error otherwise
}

Ship::Ship(std::string name, ship_type type){

	this->name = name;
	this->type = type;

}

