#include <sstream>
#include <iomanip>
#include "pd.h"

int main(int argc, char** argv) {
    if (argc == 1) {
        // Program specify
        cout << "pdadd is tool for add diary entities." << endl;
        cout << "Use \"pdadd [date]\" to add diary at specified date" << endl;
        cout << "Date format: 8-digit number" << endl << endl;
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
        ss << setw(2) << setfill('0') << ltm->tm_mon + 1 << 
            setw(2) << setfill('0') << ltm->tm_mday << 
            setw(2) << setfill('0') << ltm->tm_hour << 
            setw(2) << setfill('0') << ltm->tm_min << 
            setw(2) << setfill('0') << ltm->tm_sec;
        ss >> now;

        // Read entity in
        string content, oneLine;
        cout << "Start to write today's diary:" << endl;
        while(getline(cin, oneLine)) {
            if (oneLine == ".") 
                break;
            else 
                content += oneLine + '\001';
        }
        myDiary->insert({now, content});
        myDiary->writeDiary();
        delete myDiary;
        cout << "Diary added success." << endl;
        return 0;
    } 
    // two paras, date specified
    else if (argc == 2) {
        // check date format
        string date = string(argv[1]);
        if (date.length() != 8) {
            cout << "Error: invalid date format" << endl;
            return -1;
        }
        else {
            // read diary file in 
            Diary *myDiary = new Diary();
            if(!myDiary->readDiary()) {
                cout << "Diary not exist, create new file" << endl;
            }
            // set time
            // warning: same time(hour/min/sec) could cause problem
            time_t seconds = time(0);
            tm *ltm = localtime(&seconds);
            string now;
            stringstream ss;
            ss << date <<
            setw(2) << setfill('0') << ltm->tm_hour <<
            setw(2) << setfill('0') << ltm->tm_min <<
            setw(2) << setfill('0') << ltm->tm_sec;
            ss >> now;
            string content, oneLine;
            cout << "Start to write the day's diary:" << endl;
            while(getline(cin, oneLine)) {
                if (oneLine == ".") 
                    break;
                else 
                    content += oneLine + '\001';
            }
            myDiary->insert({now, content});
            myDiary->writeDiary();
            delete myDiary;
            cout << "Diary added success." << endl;
            return 0;
        }
    }
    else {
        cout << "Error: too much arguments" << endl;
        return -1;
    }
}