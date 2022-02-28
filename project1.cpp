#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
using namespace std;

/* this structrue is used to story the
 * students' data, and define a pointer
 * at the same time.
 */
struct Student {
    string name;
    int score1, score2, score3;
};
typedef Student *pStu;

// used to calculate the average of one student's grades
float average(pStu Stu) {
    return (Stu->score1 + Stu->score2 + Stu->score3)*1.0/3;
}

int main() {
    Student Stu[10];
    ifstream InputFile("./input.txt");

    // use three structrues to store the sum, max, and min of score1, score2 and score3.
    Student Sum, Max, Min;
    Sum.score1 = Sum.score2 = Sum.score3 = 0;
    Max.score1 = Max.score2 = Max.score3 = 0;
    Min.score1 = Min.score2 = Min.score3 = 5;
    for (int i = 0; i < 10; i++) {
        // this conditional branch differs the 1st, 2nd, 3rd and other. 
        if (i == 0) 
            cout << "Please input the 1st student's name";
        else if (i == 1) 
            cout << "Please input the 2nd student's name";
        else if (i == 2)
            cout << "Please input the 3rd student's name";
        else
            cout << "Please input the " << i + 1 << "th student's name";
        cout << " and three scores:"; 
        // input the data from the file, then calculate the sum, max and min real-time
        InputFile >> Stu[i].name >> Stu[i].score1 >> Stu[i].score2 >> Stu[i].score3;
        Sum.score1 += Stu[i].score1;
        Sum.score2 += Stu[i].score2;
        Sum.score3 += Stu[i].score3;
        Max.score1 = Stu[i].score1 > Max.score1 ? Stu[i].score1 : Max.score1;
        Max.score2 = Stu[i].score2 > Max.score2 ? Stu[i].score2 : Max.score2;
        Max.score3 = Stu[i].score3 > Max.score3 ? Stu[i].score3 : Max.score3;
        Min.score1 = Stu[i].score1 < Min.score1 ? Stu[i].score1 : Min.score1;
        Min.score2 = Stu[i].score2 < Min.score2 ? Stu[i].score2 : Min.score2;
        Min.score3 = Stu[i].score3 < Min.score3 ? Stu[i].score3 : Min.score3;
        // an echo for input
        cout << " " << Stu[i].name << " " << Stu[i].score1 << " " << Stu[i].score2 << " " << Stu[i].score3 << endl;
    }

    cout << "no      name    score1  score2  score3  average" << endl;
    for (int i = 0; i < 10; i++) {
        // output fitting to given format
        cout << left << setw(8) << i + 1 << setw(8) << Stu[i].name << setw(8) << Stu[i].score1 << setw(8) << Stu[i].score2 << setw(8) << Stu[i].score3 << setprecision(6) << average(Stu + i) << endl;
    }

    cout << left << "        average " << setw(8) << Sum.score1*1.0/10 << setw(8) << Sum.score2*1.0/10 << setw(8) << Sum.score3*1.0/10 << endl;
    cout << left << "        min     " << setw(8) << Min.score1 << setw(8) << Min.score2 << setw(8) << Min.score3 << endl;
    cout << left << "        max     " << setw(8) << Max.score1 << setw(8) << Max.score2 << setw(8) << Max.score3 << endl;
    return 0;
}