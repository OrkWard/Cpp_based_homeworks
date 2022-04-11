#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <windows.h> // use for debug
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
			m_lobbyX = m_size / 2;
			m_lobbyY = m_size / 2;
		}
		~Labyrinth() {
			for (int i = 0; i < m_size; i++) {
				delete[] m_rooms[i];
			}
			delete[] m_rooms;
		}

		int m_size;
		struct room** m_rooms;
		int m_lobbyX, m_lobbyY;
		void initialize(void);
	
	private:
		void allocPrcMst(void); // this function randomly allocate the princess and monster
		void allocDoor(void); // this function randomly create the doors
		bool reachable(int positionX, int positionY); // check whether the princess and monster room
													  // reachable from the given position
		void printMap(void); // use for debug, print the map
};
void Labyrinth::allocPrcMst(void) {
	// position for princess and monster
	int prcX, prcY;
	int monX, monY;

	// allocate a random place that doesn't spot on lobby for princess
	do {
		prcX = (int)sqrt(rand() % m_size*m_size);
		prcY = (int)sqrt(rand() % m_size*m_size);
	} while(prcX != m_lobbyX && prcY != m_lobbyY);
	m_rooms[prcX][prcY].roomType = princess;

	// allocate a random place that doesn't spot on lobby for pincess and lobby for monster
	do {
		monX = (int)sqrt(rand() % m_size*m_size);
		monY = (int)sqrt(rand() % m_size*m_size);
	} while(monX != m_lobbyX && monX != prcX && monY != m_lobbyY && monY != prcY);
	m_rooms[monX][monY].roomType = monster;
}
void Labyrinth::allocDoor(void) {
	// the door has the possibility of 60%
	for (int i = 0; i < m_size; i++) {
		for (int j = 0; j < m_size; j++) {
			if (i < m_size - 1) m_rooms[i][j].direction[1] = (rand() % 1000)*1.0 / 1000 > 0.4;
			if (j < m_size - 1) m_rooms[i][j].direction[3] = (rand() % 1000)*1.0 / 1000 > 0.4;
			if (i > 0) m_rooms[i][j].direction[0] = m_rooms[i - 1][j].direction[1];
			if (j > 0) m_rooms[i][j].direction[2] = m_rooms[i][j - 1].direction[3];
			m_rooms[i][j].doorNum = m_rooms[i][j].direction[0] + m_rooms[i][j].direction[1] + \
									m_rooms[i][j].direction[2] + m_rooms[i][j].direction[3];
		}
	}
}
bool Labyrinth::reachable(int positionX, int positionY) {
	// check if the princess is reachable
	bool reach = false;
	m_rooms[positionX][positionY].visited = true;
	if (m_rooms[positionX][positionY].roomType == monster) return false;
	else if (m_rooms[positionX][positionY].roomType == princess) return true;
	else {
		if (m_rooms[positionX][positionY].direction[0] && !m_rooms[positionX][positionY].visited)
			reach |= reachable(positionX - 1, positionY);
		if (m_rooms[positionX][positionY].direction[1] && !m_rooms[positionX][positionY].visited)
			reach |= reachable(positionX + 1, positionY);
		if (m_rooms[positionX][positionY].direction[2] && !m_rooms[positionX][positionY].visited)
			reach |= reachable(positionX, positionY - 1);
		if (m_rooms[positionX][positionY].direction[3] && !m_rooms[positionX][positionY].visited)
			reach |= reachable(positionX, positionY + 1);
	}
	return reach;
}
void Labyrinth::printMap(void) {
	// handle for cursor moving, and cursor position
	HANDLE screen = GetStdHandle(STD_OUTPUT_HANDLE);
	// cursor position
	COORD position;
	position.X = 0;
	position.Y = 2;
	SetConsoleCursorPosition(screen, position);
	
	// clear the screen
	for (int i = 0; i < 5*m_size + 1; i++){
		for (int j = 0; j < 5*m_size + 1; j++)
			cout << "  ";
		cout << endl;
	}

	SetConsoleCursorPosition(screen, position);
	for (int i = 0; i < 5*m_size + 1; i++) cout << "[]";
	cout << endl;
	for (int i = 0; i < 5*m_size; i++) cout << "[]" << endl;
	for (int i = 0; i < m_size; i++)
		for (int j = 0; j < m_size; j++) {
			position.X = 10*j + 2;
			position.Y = 5*i + 7;
			SetConsoleCursorPosition(screen, position);

			// the horizontal line
			if (m_rooms[i][j].direction[1]) cout << "[]    [][]" << endl;
			else cout << "[][][][][]" << endl;

			// the vertical line
			position.X += 8;
			position.Y -= 4;
			if (m_rooms[i][j].direction[3]) {
				SetConsoleCursorPosition(screen, position); cout << "[]"; position.Y++;
				SetConsoleCursorPosition(screen, position); cout << "  "; position.Y++;
				SetConsoleCursorPosition(screen, position); cout << "  "; position.Y++;
				SetConsoleCursorPosition(screen, position); cout << "[]"; 
			}
			else {
				SetConsoleCursorPosition(screen, position); cout << "[]"; position.Y++;
				SetConsoleCursorPosition(screen, position); cout << "[]"; position.Y++;
				SetConsoleCursorPosition(screen, position); cout << "[]"; position.Y++;
				SetConsoleCursorPosition(screen, position); cout << "[]"; 
			}

			position.X -= 7;
			position.Y -= 2;
			SetConsoleCursorPosition(screen, position);
			if (m_rooms[i][j].roomType == monster) {
				cout << "mostr" << endl;
			}
			else if (m_rooms[i][j].roomType == princess) {
				cout << "prics" << endl;
			}
			else if (m_rooms[i][j].roomType == lobby) {
				cout << "lobby" << endl;
			}
		}
	position.X = 0;
	position.Y = 5*m_size + 3;
	SetConsoleCursorPosition(screen, position);
}
void Labyrinth::initialize(void) {
	// allocate princess, monster and door, if princess or monster is
	// unreachable then reallocate
	do {
		for (int i = 0; i < m_size; i++)
			for (int j = 0; j < m_size; j++) {
				struct room* tmp = &m_rooms[i][j];
				tmp->direction[0] = tmp->direction[1] = tmp->direction[2] = tmp->direction[3] = false;
				tmp->roomType = normal;
				tmp->visited = false;
			}
		m_rooms[m_lobbyX][m_lobbyY].roomType = lobby;
		allocPrcMst();
		allocDoor();
		// uncomment the next line to enable map
		// printMap();
	} while(reachable(m_lobbyX, m_lobbyY));
}

// get the number of direction
int findDirectNum(string cmd) {
	for (int i = 0; i < 4; i++) {
		if (direction[i] == cmd) return i;
	}
	return -1;
}

// the game procedure
void gameProcedure(void) {
	// only need to record the position 
	// the player
	struct {
		int positionX;
		int positionY;
		bool meetPrc;
	} hero;
	int labySize;
	cout << "Please enter the labyrinth size:";
	do {
		cin >> labySize;
		if (labySize < 3) {
			cout << "Too small! Please enter a larger one: ";
		}
		else if (labySize > 10) {
			cout << "Too large! Please enter a small one: ";
		}
		else break;
	} while(1);

	// create the labyrinth
	Labyrinth* laby = new Labyrinth(labySize);
	laby->initialize();
	// all rooms unvisited
	for (int i = 0; i < labySize; i++)
		for (int j = 0; j < labySize; j++)
			laby->m_rooms[i][j].visited = false;

	// initial position 
	hero.positionY = laby->m_lobbyX;
	hero.positionX = laby->m_lobbyY;
	cout << "Welcome to the lobby. ";
	laby->m_rooms[hero.positionX][hero.positionY].visited = true;
	bool withPrc = false;
	while(1) {
		// enter the room
		cout << "There are " << laby->m_rooms[hero.positionX][hero.positionY].doorNum << " exit(s)";
		for (int i = 0; i < 4; i ++) {
			if (laby->m_rooms[hero.positionX][hero.positionY].direction[i]) {
				cout << "    " << direction[i];
			}
		}
		cout << endl << "Enter your command: ";

		string cmd;
		cin >> cmd;
		cin >> cmd;
		while (1) {
			while (findDirectNum(cmd) == -1) {
				cout << "Please input a legal direction, for example \"go east\":";
				cin >> cmd; cin >> cmd;
			}
			
			if (!laby->m_rooms[hero.positionX][hero.positionY].direction[findDirectNum(cmd)]) {
				cout << "This direction is Wall!" << endl;
				cin >> cmd; cin >> cmd;
				continue;
			}

			// move
			switch(findDirectNum(cmd)) {
				case 0: hero.positionX--; break;
				case 1: hero.positionX++; break;
				case 2: hero.positionY--; break;
				case 3: hero.positionY++; break;
			}
			break;
		}

		// if visited
		if (!laby->m_rooms[hero.positionX][hero.positionY].visited) {
			cout << "You've entered a new room. ";
			laby->m_rooms[hero.positionX][hero.positionY].visited = true;

			// different room types
			if (laby->m_rooms[hero.positionX][hero.positionY].roomType == monster) {
				cout << "Damn! A monster! You dead. ";
				cout << "Game Over" << endl;
				return ;
			}
			else if (laby->m_rooms[hero.positionX][hero.positionY].roomType == princess) {
				cout << "Congratulation! You find the secret room! " << endl;
				withPrc = true;

				// communicate with princess
				cout << "You see the princess. Enter to continue: \n";
				getline(cin, cmd);
				cout << "You: I will bring you out here, my princess .";
				getline(cin, cmd);
				cout << "Princess: I appreciate it. Thank you so much .";
				getline(cin, cmd);
				cout << "You: No time to wait. Let's get out now. ";
				getline(cin, cmd);
			}
		}
		else {
			if (laby->m_rooms[hero.positionX][hero.positionY].roomType == lobby) {
				if (withPrc) {
					cout << "You bring the princess out of the labyrinth! You've won the game! ";
					return ;
				}
				else {
					cout << "You've back to the lobby, but only yourself. Where is the princess? ";
					getline(cin, cmd);
				}
			} 
			else 
				cout << "You've entered a familiar room. ";
		}
	}
}

int main() {
	// seed for random numbers
	unsigned seed;
	seed = time(0);
	srand(seed);
	// game repeat
	while(1) {
		system("CLS");
		cout << "Welcome to Save the Princess." << endl;
		gameProcedure();
		cout << "Do you want to play again? [Yes(Y)/No(N)]:";
		string again;
		cin >> again;
		if (again[0] = 'Y') 
			continue;
		else 
			break;
	}
	return 0;
}