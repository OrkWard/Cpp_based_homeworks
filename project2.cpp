#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#define MAX_COURSES_NUMBER 100
using namespace std;

// This global variable store the name of all courses, whose amount less then MAX_COURSES_NUMBER
string course_names[MAX_COURSES_NUMBER] = {"Math", "Chinese", "English", "Physics", "Chemistry", "Militrary Science", \
						"Surveying", "History", "Translation", "C++ Programming"};
// This class is used to store a chain of name-score by course ID.
// Only accessed by class Student.
class Course {
	public:
		int m_course_id;
		int m_score;
		pCourse m_next;
};
typedef Course *pCourse;

// This class is used to store a student's information.
// Only manipulate by class Students.
class Student {
	private:
		string m_name;
		pCourse m_scores;
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
	for (int i = 0; i < MAX_COURSES_NUMBER; i++) {
		if (!name.compare(course_names[i])) {
			return i;
		}
	}
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
	
}
typedef Student* pStudent;

// This class store the whole students' information. 
class Students {
	public:
	 	Students() {
			m_next = NULL;
			m_stu = NULL;
		};
		Students(pStudent stu): m_stu(stu), m_next(NULL){};
		~Students() {
			delete m_stu;
		};
		void add_student(pStudent new_stu); // This function add a new student to the chain.
		void print_all_stu();	// This function print all students' information and then 
								// print the statistics data.
		pStudent m_stu;
		pStudents m_next;
		int m_max[MAX_COURSES_NUMBER], m_min[MAX_COURSES_NUMBER], m_sum[MAX_COURSES_NUMBER];
};
void Students::add_student(pStudent new_stu) {
	if (m_stu == NULL) {
		m_stu = new_stu;
		return;
	} else {
		for (pStudents p = this; ; p = p->m_next){
			if (p->m_next == NULL) {
				p->m_next = new Students(new_stu);
				return;
			}
		}
	}
}
void Students::print_all_stu() {
	if (m_stu == NULL) {
		cout << "You haven't input any students!" << endl;
	} else {
		pStudents tmp = this;
		int count = 0;
		while (tmp) {
			// TODO
		}
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