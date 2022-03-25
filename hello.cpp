#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

int main() {
	string Name;
	cout << "[]" << endl << "[]";
	cout << "0   ";
	for (int i = 0; i < 255; i++) {
		char c = i;
		cout << (char)i << " ";
		if (i % 16 == 0) cout << endl << left << setw(4) << i / 16;
	}
	cin >> Name;
	return 0;
}