#include "pd.h"

Diary::Diary(): map() {};

bool Diary::readDiary(void) {
    fstream fs(".\\pd.txt", ios::in);
    if(!fs) {
        return false;
    }
    cout << !fs;
    string date, content;
    while(getline(fs, date)) {
        getline(fs, content);
        this->insert({date, content});
    }
    return true;
}

void Diary::writeDiary(void) const {
    fstream fs("pd.txt", ios::out);
    for(const_iterator iter = this->begin(); iter != this->end(); ++iter) {
        fs << iter->first << endl;
        if (iter->first != this->rbegin()->first)
            fs << iter->second << endl;
        else
            fs << iter->second;
    }
}

void Diary::outputDiary(void) const {
    string date, content;
    for(const_iterator iter = this->begin(); iter != this->end(); ++iter) {
        date = iter->first;
        content = iter->second;
        cout << date.substr(0, 4) << '/' << date.substr(3, 2) << '/' << date.substr(5, 2) << endl;
        int pos = 0;
        while (content.find('\r', pos) >= 0) {
            cout << content.substr(pos, content.find('\r', pos) - pos - 1) << endl;
            pos = content.find('\r', pos) + 1;
        }
    }
}