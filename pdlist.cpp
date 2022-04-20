#include "pd.h"

// count the length of the char* string
int strlen(char* str) {
    int i;
    for(i = 0; str[i] != '\0'; i++);
    return i;
}

// transform the char* string to positive number, digits specified
int to_int(char* str, int len) {
    int num = 0;
    for (int i = 0; i < len; i++) {
        if (str[i] > '9' || str[0] < '0')
            return -1;
        num = num * 10 + str[i] - '0';
    }
    return num;
}

int main(int argc, char** argv) {
    // use to store the choesn diaries
    Diary *specifiedDiary = new Diary();
    // Usage description
    if(argc == 1) {
        cout << "pdlist is part of the Personal Diary, used to list the diaries." << endl << endl;
        cout << "Usage: pdlist [option] [start] [end]" << endl;
        cout << "Option" << endl 
                << "    " << "-a: List all the diaries, discard all other arguments" << endl 
                << "    " << "    specified." << endl 
                << "    " << "-r: Set the next parameter as end. Defaultly, if only" << endl 
                << "    " << "    one date specified, it will be treated as start. " << endl;
        cout << "Date format:" << endl 
                << "    " << "Both start and end should be pure numbers, 4-digits(regard" << endl 
                << "    " << "as year), 6-digits(regard as year-month) or 8-digits" << endl 
                << "    " << "(regard as year-month-day)" << endl;
        return 0;
    }
    else if(argc == 2) {
        Diary *myDiary = new Diary();
        if(!myDiary->readDiary()) {
            cout << "Error: diary file not exist" << endl;
            delete myDiary;
            return -1;
        }

        // option
        if (argv[1][0] == '-')
            // print all
            if (argv[1][1] == 'a') {
                for (Diary::iterator iter = myDiary->begin(); iter != myDiary->end(); iter++) {
                    cout << iter->first.substr(0, 4) << '/' << iter->first.substr(3, 2) << '/'
                        << iter->first.substr(5, 2) << endl;
                    int pos = 0;
                    while(iter->second.find('\r', pos) >= 0) {
                        cout << iter->second.substr(pos, iter->second.find('\r', pos) - 1 - pos);
                        pos = iter->second.find('\r', pos) + 1;
                    }
                }
                delete myDiary;
                return 0;
            }

            // param -r without date, invalid
            else if(argv[1][1] == 'r') {
                cout << "Error: invalid usage" << endl;
                delete myDiary;
                return -1;
            }
            else {
                cout << "Error: invalid option" << endl;
                delete myDiary;
                return -1;
            }
        // one date specified, treated as start
        else {
            string *specifiedDate = new string(argv[1]);
            int dateLen = specifiedDate->length();
            if (dateLen != 4 || dateLen != 6 || dateLen != 8) {
                cout << "Error: invalid date type" << endl;
                delete myDiary;
                return -1;
            }
            else {
                // don't care about date detail, just compare
                for (Diary::iterator iter = myDiary->begin(); iter != myDiary->end(); iter++) {
                    if (iter->first.substr(0, dateLen) >= *specifiedDate) 
                        specifiedDiary->insert({iter->first, iter->second});
                }
            }
            delete specifiedDate;
        }
    }
    else if (argc == 3) {
        Diary *myDiary = new Diary();
        if(!myDiary->readDiary()) {
            cout << "Error: diary file not exist" << endl;
            delete myDiary;
            return -1;
        }
        if (argv[0][1] == '-') {
            // print all
            if (argv[1][1] == 'a') {
                for (Diary::iterator iter = myDiary->begin(); iter != myDiary->end(); iter++) {
                    cout << iter->first.substr(0, 4) << '/' << iter->first.substr(3, 2) << '/'
                        << iter->first.substr(5, 2) << endl;
                    int pos = 0;
                    while(iter->second.find('\r', pos) >= 0) {
                        cout << iter->second.substr(pos, iter->second.find('\r', pos) - 1 - pos);
                        pos = iter->second.find('\r', pos) + 1;
                    }
                }
                delete myDiary;
                return 0;
            }
            
            // one date specified, treated as end
            else if (argv[1][1] == 'r') {
                string *specifiedDate = new string(argv[2]);
                int dateLen = specifiedDate->length();
                for (Diary::iterator iter = myDiary->begin(); iter != myDiary->end(); iter++) {
                    if (iter->first.substr(0, dateLen) <= *specifiedDate) 
                        specifiedDiary->insert({iter->first, iter->second});
                }
                delete specifiedDate;
            }
            else {
                cout << "Error: invalid option" << endl;
                delete myDiary;
                return -1;
            }
        }
        
        // two date specified
        else {
            string *start = new string(argv[1]);
            string *end = new string(argv[2]);
            int startLen = start->length();
            int endLen = end->length();
            Diary *specifiedDiary = new Diary();
            for (Diary::iterator iter = myDiary->begin(); iter != myDiary->end(); iter++) {
                if (iter->first.substr(0, startLen) >= *start && iter->first.substr(0, endLen) <= *end) 
                    specifiedDiary->insert({iter->first, iter->second});
            }
            delete start, end;
        }
    }
    else {
        cout << "Error: Too much arguments" << endl;
        return -1;
    }

    // print the chosen diaries
    if (specifiedDiary->size() == 0) {
        cout << "Error: cannot find diary entity according to the specified date" << endl;
        delete specifiedDiary;
        return -1;
    }
    else {
        cout << "Find " << specifiedDiary->size() << " diaries: " << endl;
        specifiedDiary->outputDiary();
        delete specifiedDiary;
        return 0;
    }
}