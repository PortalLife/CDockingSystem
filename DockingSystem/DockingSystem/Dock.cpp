#include <array>
#include "Port.h"


// constructor for docks: creates 10 rows

Dock::Dock(){

	for (int i = 0; i < Dock::rows.size(); i++){

		rows[i] = new Row;
	}

}

std::array<Row*, 10> Dock::getRows(){

	return this->rows;

}
