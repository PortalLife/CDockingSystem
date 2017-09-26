#include "Port.h"

// constructing the berths and setting their type
Row::Row(){

	int i = 0;
	for (i = 0; i < 5; i++)
	{

		Berth* newBerth = new Berth(ship_type::cargo);
		berths[i] = newBerth;

	}
	for (i = 5; i < 8; i++)
	{

		Berth* newBerth = new Berth(ship_type::container);
		berths[i] = newBerth;
	}
	for (i = 8; i < 10; i++)
	{

		Berth* newBerth = new Berth(ship_type::super);
		berths[i] = newBerth;
	}
}

// getter function
std::array<Berth*, 10>* Row::getBerths(){

	return &this->berths;

}