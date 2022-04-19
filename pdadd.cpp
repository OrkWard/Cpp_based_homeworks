#include "pd.h"

int main(int argc, char** argv) {
    cout << "pdadd is tool for add diary entities." << endl << endl;
    Diary *myDiary = new Diary();
    if(!myDiary->readDiary()) {
        cout << "Diary file not exist. Create new file." << endl;
    }
    time_t seconds = time(0);
    tm *ltm = localtime(&seconds);
    string now = to_string(ltm->tm_year + 1900) + to_string(ltm->tm_mon + 1) + to_string(ltm->tm_mday) + \
                to_string(ltm->tm_hour) + to_string(ltm->tm_min) + to_string(ltm->tm_sec);
    string content, oneLine;
    cout << "Start to write today's diary:" << endl;
    while(getline(cin, oneLine)) {
        if (oneLine == "") break;
        else content += oneLine + '\x00';
    }
    myDiary->insert({now, content});
    myDiary->writeDiary();
    cout << "Diary added success." << endl;
    return 0;
}