#ifndef __PERSONALDIARY__
#define __PERSONALDIARY__
#include <iostream>
#include <fstream>
#include <String>
#include <map>
using namespace std;

// store all entities of diary, inherit from map
class Diary: public map<long, string> {
	public:
		bool readDiary(void);	// read diary from local file, return whether succeed or not
		bool writeDiary(void) const;	// write the file to the local file
};
#endif