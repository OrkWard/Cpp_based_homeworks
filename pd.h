#ifndef __PERSONALDIARY__
#define __PERSONALDIARY__
#include <iostream>
#include <fstream>
#include <String>
#include <map>
#include <ctime>
using namespace std;

// store all entities of diary, inherit from map
class Diary: public map<string, string> {
	public:
		Diary(); // initialize
		bool readDiary(void);	// read diary from local file, return whether succeed or not
		void writeDiary(void) const;	// write the file to the local file
};
#endif