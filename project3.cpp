#include <iostream>
#include <sstream>
#include <string>
using namespace std;

// four type of room type
enum ROOMTYPE {
	normal, lobby, princess, monster
};

// direction array
const string direction[4] = {"up", "down", "west", "east"};

// Store one room's info, room type, whether rooms 
// around accessable, and whether visited.
struct room {
	ROOMTYPE roomType;
	int doorNum;
	bool direction[4];
	bool visited = false;
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

struct player {
	int positionX;
	int positionY;
	bool meetPrc;
};

int findDirectNum(string cmd) {
	for (int i = 0; i < 4; i++) {
		if (direction[i] == cmd) return i;
	}
}

int main() {
	// only need to record the position 
	// the player
	struct player hero;

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

}

bool gameProcedure(struct player hero, Labyrinth* laby) {
	bool withPrc = false;
	while(1) {
		string cmd;
		cin >> cmd;
		stringstream ss(cmd);
		ss >> cmd; ss >> cmd;

		// move
		switch(findDirectNum(cmd)) {
			case 0: hero.positionY++; break;
			case 1: hero.positionY--; break;
			case 2: hero.positionX--; break;
			case 3: hero.positionX++; break;
		}
		
		// if visited
		if (!laby->m_rooms[hero.positionX][hero.positionY].visited) {
			cout << "You've entered a new room. ";
			laby->m_rooms[hero.positionX][hero.positionY].visited = true;

			// different room types
			if (laby->m_rooms[hero.positionX][hero.positionY].roomType == monster) {
				cout << "Damn! A monster! You dead.";
				cout << "Game Over";
				return 0;
			}
			else if (laby->m_rooms[hero.positionX][hero.positionY].roomType == princess) {
				cout << "Congratulation! You find the secret room!" << endl;
				cout << "You see the princess. Enter to continue:" << endl;
				getline(cin, cmd);
				cout << "You: I will bring you out here, my princess." << endl;
				getline(cin, cmd);
				cout << "Princess: I appreciate it. Thank you so much." << endl;
				getline(cin, cmd);
				cout << "You: No time to wait. Let's get out now." << endl;
				getline(cin, cmd);
			}
		}
		else {
			if (laby->m_rooms[hero.positionX][hero.positionY].roomType == lobby) {
				if (withPrc) {
					cout << "You bring the princess out of the labyrinth! You've won the game!";
					return 0;
				}
				else {
					cout << "You've back to the lobby, but only yourself. Where is the princess?";
					getline(cin, cmd);
				}
			} 
			else 
				cout << "You've entered a familiar room. ";
		}

		// Go to next room.
		cout << "There are " << laby->m_rooms[hero.positionX][hero.positionY].doorNum << " exit(s)";
		for (int i = 0; i < 4; i ++) {
			if (laby->m_rooms[hero.positionX][hero.positionY].direction[i]) {
				cout << "    " << direction[i];
			}
		}
		cout << endl << "Enter your command: ";
	}
}