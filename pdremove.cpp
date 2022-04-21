#include "pd.h"

int main(int argc, char** argv) {
    if (argc == 1) {
        cout << "pdremove is used to remove a diary from file" << endl;
        cout << "Usage: pdremove [date]" << endl;
        cout << "Date format: 4-digts, 6-digits or 8-digits number" << endl;
        return -1;
    }
    else if (argc == 2) {
        string date = string(argv[1]);
        int dateLen = date.length();
        if (dateLen != 4 && dateLen != 6 && dateLen != 8) {
            cout << "Error: invalid date format" << endl;
            return -1;
        }
        else {
            Diary myDiary;
            if (!myDiary.readDiary()) {
                cout << "Error: diary file not exist" << endl;
                return -1;
            }
            else {
                Diary specifiedDiary;
                for (auto iter = myDiary.begin(); iter != myDiary.end(); iter++) {
                    if (iter->first.substr(0, dateLen) == date)
                        specifiedDiary.insert({iter->first, iter->second});
                }
                if (specifiedDiary.size() == 0) {
                    cout << "Error: diary not found" << endl;
                    return -1;
                }
                else if(specifiedDiary.size() == 1) {
                    myDiary.erase(specifiedDiary.begin()->first);
                    myDiary.writeDiary();
                    cout << "Delete diary succeed." << endl;
                    return 0;
                }
                else {
                    cout << "Multiple diaries found:" << endl;
                    specifiedDiary.outputDiary();
                    cout << "please indicate the diary to delete: [1 to " << specifiedDiary.size() << "]" << endl;
                    int index, i = 1;
                    cin >> index;
                    for (auto iter = specifiedDiary.begin(); iter != specifiedDiary.end(); iter++) {
                        if (i == index) {
                            myDiary.erase(iter->first);
                            myDiary.writeDiary();
                            cout << "Delete diary succeed." << endl;
                            return 0;
                        }
                        i++;
                    }

                    cout << "Error: index out of range" << endl;
                    return -1;
                }
            }
        }
    }
    else {
        cout << "Error: too many arguments" << endl;
        return -1;
    }
}