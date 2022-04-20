#include <sstream>
#include <iomanip>
#include "pd.h"

int main(int argc, char** argv) {
    // Program specify
    cout << "pdadd is tool for add diary entities." << endl << endl;
    Diary *myDiary = new Diary();
    if(!myDiary->readDiary()) {
        cout << "Diary not exist, create new file" << endl;
    }

    // Set time
    time_t seconds = time(0);
    tm *ltm = localtime(&seconds);
    string now;
    stringstream ss;
    ss << ltm->tm_year + 1900;
    ss << setw(2) << setfill('0') << ltm->tm_mon + 1 << ltm->tm_mday << ltm->tm_hour << ltm->tm_min << ltm->tm_sec;
    ss >> now;

    // Read entity in
    string content, oneLine;
    cout << "Start to write today's diary:" << endl;
    while(getline(cin, oneLine)) {
        if (oneLine == ".") 
            break;
        else 
            content += oneLine + '\0';
    }
    myDiary->insert({now, content});
    myDiary->writeDiary();
    delete myDiary;
    cout << "Diary added success." << endl;
    return 0;
}