#include <array>

// enum for ship type - sets the types as 0, 1, 2
enum ship_type : unsigned { cargo, container, super };

class Ship {
private:
	ship_type type;
	std::string name;

public:

	Ship();
	Ship(std::string name, ship_type type);
	ship_type getType()
	{
		return type;
	}
	std::string getName()
	{
		return name;
	}

};

class Berth {

public:

	Ship* dockedShip;
	ship_type capacity;

public:
	Berth();
	Berth(ship_type capacity);

};

class Row {

private:
	std::array<Berth*, 10> berths;

public:
	std::array<Berth*, 10>* getBerths();
	Row();
};

class Dock {

private:
	std::array<Row*, 10> rows;

public:
	std::array<Row*, 10> getRows();
	Dock();


};

class Port {

public:
	void AddShip(std::string InputName, ship_type InputType);
	void RemoveShip(std::string InputName);
	void StatusReport();
	Port();

private:
	std::array<Ship*, 10> waiting_list;
	std::array<Dock*, 3> docks;

};