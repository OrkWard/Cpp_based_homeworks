#include <iostream>
#include <sstream>
#include <string>
using namespace std;

// four type of room type
enum ROOMTYPE {
	normal, lobby, princess, monster
};

// Store one room's info, room type, whether rooms 
// around accessable, and whether visited.
struct room {
	ROOMTYPE roomType;
	int doorNum;
	bool direction[4];
	bool visited;
};

// Store the whole labyrinth
class Labyrinth {
	public:
		Labyrinth(int size): m_size(size){
			m_rooms = new struct room*[size];
			for (int i = 0; i < size; i++) {
				m_rooms[i] = new struct room[size];
			}
		}
		~Labyrinth() {
			for (int i = 0; i < m_size; i++) {
				delete[] m_rooms[i];
			}
			delete[] m_rooms;
		}

		int m_size;
		struct room** m_rooms;
		void initialize(void);
	
	private:
		void allocPrcMst(void); // this function randomly allocate the princess and monster
		void constrDoor(void); // this function randomly create the doors
		bool reachable(void); // check the labyrinthe is whether legal or not
};
void Labyrinth::allocPrcMst(void) {
	// todo
}
void Labyrinth::constrDoor(void) {
	// todo
}
bool Labyrinth::reachable(void) {
	// todo
}
void Labyrinth::initialize(void) {

}

int findDirectNum(string cmd) {
	const string direction[4] = {"up", "down", "west", "east"};
	for (int i = 0; i < 4; i++) {
		if (direction[i] == cmd) return i;
	}
}

int main() {
	// only need to record the position 
	// the player
	struct {
		int positionX;
		int positionY;
		bool meetPrc;
	} hero;

	int labySize;
	cout << "Welcome to Save the Princess." << endl << "Please enter the labyrinth size:" << endl;
	do {
		cin >> labySize;
		if (labySize < 3) {
			cout << "Too small! Please enter a larger one: ";
		}
		else if (labySize > 20) {
			cout << "Too large! Please enter a small one: ";
		}
		else break;
	} while(1);

	// create the labyrinth
	Labyrinth* laby = new Labyrinth(labySize);
	laby->initialize();

	// initial position 
	hero.positionY = 0;
	hero.positionX = (labySize + 1) / 2;
	cout << "Welcome to the lobby. There are 3 exits: east, west, and up." << endl;
	cout << "Enter your command: ";
	
	// the game procedure
	while(1) {
		string cmd;
		cin >> cmd;
		stringstream ss(cmd);
		ss >> cmd; ss >> cmd;
		switch(findDirectNum(cmd)) {
			case 0: hero.positionY++; break;
			case 1: hero.positionY--; break;
			case 2: hero.positionX--; break;
			case 3: hero.positionX++; break;
		}
		if (laby->m_rooms[hero.positionX][hero.positionY].visited) {
			cout << "You've entered a new room. ";
		}
		cout << "There are " << laby->m_rooms[hero.positionX][hero.positionY].doorNum;
	}
}