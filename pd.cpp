#include "pd.h"

Diary::Diary(): map() {};

bool Diary::readDiary(void) {
    fstream fs("pd.txt", ios::in);
    if(!fs) return false;
    string date, content;
    while(getline(fs, date)) {
        getline(fs, content);
        this->insert({date, content});
    }
    return true;
}

void Diary::writeDiary(void) const{
    fstream fs("pd.txt", ios::out);
    string date, content;
    for(const_iterator iter = this->begin(); iter != this->end(); ++iter) {
        fs << iter->first << endl;
        if (iter->first != this->rbegin()->first)
            fs << iter->second << endl;
        else
            fs << iter->second;
    }
}