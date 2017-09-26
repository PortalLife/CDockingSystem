#include <string>
#include <array>
#include <fstream>
#include "Port.h"
#include <iostream>
#include <ctime>

// constructor to create our docks and fill the waiting list with null pointers:

Port::Port(){

	waiting_list.fill(nullptr);

	for (int i = 0; i < docks.size(); i++) {
		docks[i] = new Dock();
	}

}

// global variable for writing to the PortLog

std::fstream report;

void Port::AddShip(std::string InputName, ship_type InputType){

	/// Create a ship based on the parameters passed

	Ship* theShip = new Ship(InputName, InputType);

	// struct for the time - used for the portlog.txt

	time_t TheTime;
	struct tm * timedetails;

	time(&TheTime);
	timedetails = localtime(&TheTime);

	// A for loop that goes through the arrays and then finds the first available space and then
	// Assigns the ship object to that space.

	// boolean flag to indicate if the ship docking has been successful - important to the operation of docking a ship.
	bool success = false;

	for (int i = 0; i < docks.size(); i++)
	{

		// pointer to the current dock in the for loop

		Dock* currentDock = docks[i];

		for (int x = 0; x < currentDock->getRows().size(); x++){
			// for each row
			Row* currentRow = currentDock->getRows()[x];
			int berthSize = currentRow->getBerths()->size();
			for (int y = 0; y < berthSize; y++){

				Berth* currentBerth = currentRow->getBerths()->at(y);


				if (currentBerth->dockedShip == nullptr && currentBerth->capacity == theShip->getType()){

					// you've found an EXACT match, and you can dock the ship
					success = true;
					currentBerth->dockedShip = theShip;
					std::cout << "The ship " << InputName << ", type " << InputType << " has successfully docked at dock " << i << ", Row " << x << ", berth " << y << "\n";
					report.open("PortLog.txt", std::fstream::app);
					report << "Ship " << InputName << " has docked at dock " << i << ", Row " << x << ", berth " << y << "\n" << " at time " << asctime(timedetails);
					report.close();
					return;

				}
			}
		}
	}

	if (!success)
	{

		for (int i = 0; i < docks.size(); i++)
		{

			Dock* currentDock = docks[i];

			for (int x = 0; x < currentDock->getRows().size(); x++){

				Row* currentRow = currentDock->getRows()[x];
				int berthSize = currentRow->getBerths()->size();
				for (int y = 0; y < berthSize; y++){

					// create a pointer to the current berth

					Berth* currentBerth = currentRow->getBerths()->at(y);

					if (currentBerth->dockedShip == nullptr && currentBerth->capacity >= theShip->getType()){
						// you've found a match THAT FITS, and you can dock the ship
						success = true;
						currentBerth->dockedShip = theShip;
						std::cout << "The ship " << InputName << ", type " << InputType << " has successfully been added to Dock " << i << ", Row " << x << ", berth" << y << "\n";
						report.open("PortLog.txt", std::fstream::app);
						report << "Ship " << InputName << " has docked at dock " << i << ", Row " << x << ", berth " << y << "\n" << " at time " << asctime(timedetails);
						report.close();
						return;

					}
				}
			}
		}
	}

	if (!success) // If the port is full, add to the waiting list.
	{
		for (int i = 0; i < 10; i++){
			if (waiting_list[i] == nullptr){
				waiting_list[i] = theShip;
				success = true;
				std::cout << "The ship " << InputName << " Has been successfully added to the waiting list. \n";
				report.open("PortLog.txt", std::fstream::app);
				report << "Ship " << InputName << " has been added to the waiting list" << " at time " << asctime(timedetails);
				report.close();
				return;
			}
		}
	}

	if (!success) // Turn away the ship (DESTROY)
	{
		std::cout << "The ship " << InputName << " was unable to be docked or added to the waiting list and was turned away. \n";
		report.open("PortLog.txt", std::fstream::app);
		report << "Ship " << InputName << " was turned away " << " at time " << asctime(timedetails);
		report.close();
		delete theShip;
	}

}


void Port::RemoveShip(std::string InputName){


	
	time_t TheTime;
	struct tm * timedetails;

	time(&TheTime);
	timedetails = localtime(&TheTime);

	for (int i = 0; i < docks.size(); i++)
	{
	
		Dock* currentDock = docks[i];

		for (int x = 0; x < currentDock->getRows().size(); x++){
		
			Row* currentRow = currentDock->getRows()[x];
			int berthSize = currentRow->getBerths()->size();
			for (int y = 0; y < berthSize; y++){

				Berth* currentBerth = currentRow->getBerths()->at(y);

				// used to prevent memory access violations
				if (currentBerth->dockedShip == nullptr){
					std::cout << "This ship does not exist!\n";
					return;
				}

				// if the input name matches with the name of any ship - delete it and replace it with nullptr
				if (currentBerth->dockedShip->getName() == InputName){

					std::cout << "Ship " << InputName << " Successfully deleted from dock " << i << ", Row " << x << ", berth " << y << "\n";
					report.open("PortLog.txt", std::fstream::app);
					report << "Ship " << InputName << " has undocked from dock " << i << ", Row " << x << ", berth " << y << "\n" << " at time " << asctime(timedetails);
					report.close();

					currentBerth->dockedShip = nullptr;
				
					// Sucessfully deleted a ship - now run a for loop through the waiting list and add a ship from the waiting list to the port

					for (int i = 0; i < 10; i++){

						if (waiting_list[i] != nullptr && currentBerth->capacity >= waiting_list[i]->getType()){

							currentBerth->dockedShip = waiting_list[i];
							std::cout << "The ship " << waiting_list[i]->getName() << "	has been added to dock " << i << ", Row " << x << ", berth " << y << " from the waiting list \n";
							waiting_list[i] = nullptr;
							return;
						}
					}
					return;
				}
			}
		}
	}
}

void Port::StatusReport(){

	// Counting the number of free spaces and their type with 4 unsigned ints.

	unsigned int count = 0;
	unsigned int smallcount = 0;
	unsigned int mediumcount = 0;
	unsigned int largecount = 0;


	for (int i = 0; i < docks.size(); i++)
	{

		Dock* currentDock = docks[i];

		for (int x = 0; x < currentDock->getRows().size(); x++){
		
			Row* currentRow = currentDock->getRows()[x];
			int berthSize = currentRow->getBerths()->size();
			for (int y = 0; y < berthSize; y++){

				Berth* currentBerth = currentRow->getBerths()->at(y);

				if (currentBerth->dockedShip == nullptr){
					count++;
				}
				if (currentBerth->dockedShip == nullptr && currentBerth->capacity == 0){
					smallcount++;
				}
				if (currentBerth->dockedShip == nullptr && currentBerth->capacity == 1){
					mediumcount++;
				}
				if (currentBerth->dockedShip == nullptr && currentBerth->capacity == 2){
					largecount++;
				}


			}

		}

	}

	std::cout << "There are currently " << count << " open spots in the port. \n";
	std::cout << smallcount << " Of these are spaces for Cargo Ships \n";
	std::cout << mediumcount << " Of these are spaces for Container Ships \n";
	std::cout << largecount << " Of these are spaces for Super Ships \n";
	std::cout << "The ships currently docked are: \n";

	for (int i = 0; i < docks.size(); i++)
	{


		Dock* currentDock = docks[i];

		for (int x = 0; x < currentDock->getRows().size(); x++){

			Row* currentRow = currentDock->getRows()[x];
			int berthSize = currentRow->getBerths()->size();
			for (int y = 0; y < berthSize; y++){

				Berth* currentBerth = currentRow->getBerths()->at(y);

				if (currentBerth->dockedShip == nullptr){

					return;
				}

				std::cout << currentBerth->dockedShip->getName() << std::endl;
			}

		}

	}
	std::cout << "The ships in the waiting list are: ";
	for (int i = 0; i < 10; i++){

		std::cout << waiting_list[i]->getName();
		if (waiting_list[i] == nullptr){
			return;
		}

	}

}








