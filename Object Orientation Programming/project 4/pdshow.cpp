#include "pd.h"
#define MAX_DIARY_LENGTH 6000

int main(int argc, char** argv) {
    if (argc == 1) {
        cout << "pdshow is part of Personal Diary, used to show diaries." << endl << endl;
        cout << "Usage: pdshow [date]" << endl;
        cout << "Date format: 8-digits number" << endl;
        return 0;
    }
    else if(argc == 2) {
        string date = string(argv[1]);
        if (date.length() != 8) {
            cout << "Error: invalid date format" << endl;
            return -1;
        }
        else {
            string cmd = "pdlist " + date + " " + date;
            FILE *fp = popen(cmd.c_str(), "rt");
            char oneLine[MAX_DIARY_LENGTH];
            while(fgets(oneLine, MAX_DIARY_LENGTH, fp) != NULL) {
                cout << oneLine;
            }
            pclose(fp);
            return 0;
        }
    }
    else {
        cout << "Error: too many arguments" << endl;
        return -1;
    }
}