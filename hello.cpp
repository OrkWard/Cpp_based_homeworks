#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int main() {
	string Name;

	getline(cin, Name);
	stringstream ss(Name);
	ss >> Name;
	cout << Name << endl;
	ss >> Name;
	cout << Name << endl;
	getline(cin, Name);
	ss.str(Name);
	ss.clear();
	Name.clear();
	ss >> Name;
	cout << Name << endl;
	cout << "hello world! " << Name << endl;
	return 0;
}