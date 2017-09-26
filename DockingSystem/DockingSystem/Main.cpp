#include <iostream>
#include "Port.h"
#include <string>

int main() {

	// Global variables to be used for the program

	std::string InputName;
	Port MyPort;
	int InputTypeInt;
	ship_type InputType;

	// Program will loop as long as the user doesn't exit or invalid input is received.

	while (true){
	
		std::cout << "Welcome to the port system. Please choose an option. \n";
		std::cout << "1 - Add a ship to the port. \n";
		std::cout << "2 - Remove a ship from the port. \n";
		std::cout << "3 - Status report on the port. \n";
		std::cout << "4 - Quit the program. \n";

		unsigned int input;

		std::cin >> input;

		switch (input){

		case 1:
			
			std::cout << "Please enter the ship name \n ";
			std::cin >> InputName;
			std::cout << "Please enter the ship type. Enter 0 for a small ship, 1 for medium, 2 for large.\n";
			std::cin >> InputTypeInt;
             
			if (InputTypeInt > 2 || InputTypeInt < 0){

				std::cout << "This is not a valid type of ship!\n";
				system("pause");
				return 0;
			}
			MyPort.AddShip(InputName, (ship_type)InputTypeInt);
			break;

		case 2:
			
			std::cout << "Please enter the ship name to be deleted \n";
			std::cin >> InputName;
			MyPort.RemoveShip(InputName);
			break;

		case 3:

			MyPort.StatusReport();
			break;

		case 4: return 0;

		default:
			
			std::cout << "Invalid input!\n";
			system ("pause");
			return 0;
		};
	}
}


