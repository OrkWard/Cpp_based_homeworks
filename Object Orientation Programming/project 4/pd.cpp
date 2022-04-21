#include "pd.h"

Diary::Diary(): map() {};

bool Diary::readDiary(void) {
    fstream fs(".\\pd.txt", ios::in);
    if(!fs) {
        return false;
    }
    string date, content;
    while(getline(fs, date)) {
        getline(fs, content);
        this->insert({date, content});
    }
    fs.close();
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
        cout << date.substr(0, 4) << '/' << date.substr(4, 2) << '/' << date.substr(6, 2) << ":" << endl;
        int pos = 0;
        while (iter->second.find('\001', pos) < iter->second.length()) {
            cout << content.substr(pos, content.find('\001', pos) - pos) << endl;
            pos = content.find('\001', pos) + 1;
        }
    }
}