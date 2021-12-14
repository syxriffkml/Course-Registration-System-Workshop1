#ifndef FUNCTION_H
#define FUNCTION_H

using namespace std;

class function {
	public:
		static void ConnectionFunction();
		void WriteInColor(unsigned short,string);
		void mainMenu();
		void registration();
		int studentLogin(); //STUDENT PARTS
		void studentMenu();
		void displayFacultyAndCourses();
		void studentDetail();
		void editStudentDisplay(); 
		void addGradesMenu();
		void addGrades();
		void applicationMenu();
		void application();
		int adminLogin(); //ADMIN PARTS
		void adminMenu();
};

#endif 




