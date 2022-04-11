#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#define COURSES_NUMBER 10
using namespace std;

// This global variable store the name of all courses, whose amount less then COURSES_NUMBER
string course_names[COURSES_NUMBER] = {"Math", "Chinese", "English", "Physics", "Chemistry", "Militrary", \
						"Surveying", "History", "Translation", "C++"};
// This class is used to store a chain of name-score by course ID.
// Only accessed by class Student.
class Course {
	public:
		int m_course_id;
		int m_score;
		Course* m_next;
};
typedef Course *pCourse;

// This class is used to store a student's information.
// Only manipulate by class Students.
class Student {
	private:
		void add_score(int id, int score); // This function add a course and its score
												// to the current student
		int find_course_id(string name);

	public:
		// Constructor
	 	Student() {
			m_name = "";
			m_scores = NULL;
		};
		// Destroyer
		~Student() {
			pCourse tmp;
			if (tmp = m_scores) {
				m_scores = m_scores->m_next;
				delete tmp;
			}
		};
		void read_stu(istream* inputFile); // This function read a line, get the
																// name and scores
		void print_stu(); // This function print a line with No, name and score
		pCourse m_scores;
		string m_name;
};
void Student::add_score(int id, int score) {
	pCourse p = new Course, tmp;
	p->m_course_id = id;
	p->m_score = score;
	p->m_next = NULL;
	if (m_scores == NULL) {
		m_scores = p;
	} else {
		for (tmp = m_scores; tmp->m_next; tmp = tmp->m_next);
		tmp->m_next = p;
	}
}
int Student::find_course_id(string name) {
	for (int i = 0; i < COURSES_NUMBER; i++) {
		if (!name.compare(course_names[i])) {
			return i;
		}
	}
	return -1;
}
void Student::read_stu(istream* inputFile) {
	string input, name;
	int score;

	getline(*inputFile, input);
	stringstream ss(input);
	ss >> m_name;
	while(ss >> name) {
		if (isdigit(name[0])) {
			ss >> score;
			add_score(stoi(name), score);
		} else {
			ss >> score;
			add_score(find_course_id(name), score);
		}
	}
}
void Student::print_stu() {
	cout << left << setw(8) << m_name;
	for (int i; i < COURSES_NUMBER; i++) {
		pCourse pc = m_scores;
		bool hasCourse = false;
		while (pc != NULL) {
			if (pc->m_course_id == i) {
				cout << left << setw(course_names[i].length() + 2) << pc->m_score;
				hasCourse = true;
				break;
			}
			pc = pc->m_next;
		}
		if (!hasCourse) {
			cout << left << setw(course_names[i].length() + 2) << "/";
		}
	}
	cout << endl;
}
typedef Student* pStudent;

// This class store the whole students' information. 
class Students {
	public:
	 	Students() {
			m_next = NULL;
			m_stu = NULL;
			for (int i = 0; i < COURSES_NUMBER; i++) m_min[i] = 6;
		};
		Students(pStudent stu): m_stu(stu), m_next(NULL){};
		~Students() {
			delete m_stu;
		};
		void add_student(pStudent new_stu); // This function add a new student to the chain.
		void print_all_stu();	// This function print all students' information and then 
								// print the statistics data.
		pStudent m_stu;
		Students* m_next;
		int m_max[COURSES_NUMBER] = {0}, m_min[COURSES_NUMBER] = {0}, \
			m_sum[COURSES_NUMBER] = {0}, m_count[COURSES_NUMBER] = {0};
};
void Students::add_student(pStudent new_stu) {
	if (m_stu == NULL) {
		m_stu = new_stu;
	} else {
		for (Students* p = this; ; p = p->m_next){
			if (p->m_next == NULL) {
				p->m_next = new Students(new_stu);
				break;
			}
		}
	}
	for (int i = 0; i < COURSES_NUMBER; i++) {
		pCourse pc = new_stu->m_scores;
		while(pc != NULL) {
			if (pc->m_course_id == i) {
				m_max[i] = m_max[i] > pc->m_score ? m_max[i] : pc->m_score;
				m_min[i] = m_min[i] < pc->m_score ? m_min[i] : pc->m_score;
				m_sum[i] += pc->m_score;
				m_count[i]++;
			}
			pc = pc->m_next;
		}
	}
	return;
}
void Students::print_all_stu() {
	if (m_stu == NULL) {
		cout << "You haven't input any students!" << endl;
	} else {
		cout << "no  name    ";
		for (int i = 0; i < COURSES_NUMBER; i++) {
			cout << left << setw(course_names[i].length() + 2) << course_names[i];
		}
		cout << endl;
		Students* tmp = this;
		int count = 0;
		while (tmp) {
			count++;
			cout << left << setw(4) << count;
			tmp->m_stu->print_stu();
			tmp = tmp->m_next;
		}
		cout << left << setw(12) << "Maximum";
		for (int i = 0; i < COURSES_NUMBER; i++) {
			if (m_max[i] == 0) {
				cout << left << setw(course_names[i].length() + 2) << "/";
			} else {
				cout << left << setw(course_names[i].length() +2) << m_max[i];
			}
		}
		cout << endl << left << setw(12) << "Minimum";
		for (int i = 0; i < COURSES_NUMBER; i++) {
			if (m_min[i] == 6) {
				cout << left << setw(course_names[i].length() + 2) << "/";
			} else {
				cout << left << setw(course_names[i].length() +2) << m_min[i];
			}
		}
		cout << endl << left << setw(12) << "Average";
		for (int i = 0; i < COURSES_NUMBER; i++) {
			if (m_sum[i] == 0) {
				cout << left << setw(course_names[i].length() + 2) << "/";
			} else {
				cout << left << setw(course_names[i].length() +2) << setprecision(3) << m_sum[i]*1.0/m_count[i];
			}
		}
		cout << endl;
	}
}
typedef Students* pStudents;

int main() {
	int cmd;
	pStudents Stus = new Students;
	pStudent Stu = NULL;
	ifstream inputFile("./input2.txt");
	while(1) {
		cout << "Press 1 to add a student's information, 2 to show the statistics, 3 to quit:";
		cout << endl;
		inputFile >> cmd;
		if (cmd == 1) {
			Stu = new Student();
			Stu->read_stu(&inputFile);
			Stus->add_student(Stu);
		} else if (cmd == 2) {
			Stus->print_all_stu();	
		} else if (cmd == 3) {
			return 0;
		}
	}
}