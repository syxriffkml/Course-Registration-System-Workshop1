#ifndef FUNCTION_H
#define FUNCTION_H

using namespace std;

class function {
	public:
		static void ConnectionFunction();
		void WriteInColor(unsigned short,string); 
		void mainMenu();
		void registration();
		int studentLogin(); //  START OF STUDENT PARTS
		void studentMenu();
		void displayFacultyAndCourses();
		void studentDetail();
		void editStudentDisplay(); 
		void addGradesMenu();
		void addGrades();
		void applicationMenu();
		void application();
		void viewApplication();
		void applicationResult();
		int adminLogin(); //  START OF ADMIN PARTS
		void adminMenu();
		void adminViewGraphMenu();
		void adminViewGraph();
		void adminStudentListMenu();
		void adminViewStudentList();
		void adminApproval();
};

#endif 


/*

		cout << "=================================================================================================================" << endl;
		cout << "|                                                 APPLICATION INFO                                              |" << endl;
		cout << "|---------------------------------------------------------------------------------------------------------------|" << endl;
		cout << "| Course Code | Course Name                                                                      |              |" << endl;
		cout << "|===============================================================================================================|" << endl;
		cout << "| ASDADASD    | Bachelor of Chemical Engineering Technology(Environment) with Honours            | APPROVED     |" << endl;
		cout << "|---------------------------------------------------------------------------------------------------------------|" << endl;
		cout << "| ASDADASD    | Bachelor of Chemical Engineering Technology(Environment) with Honours            | APPROVED     |" << endl;
		cout << "|---------------------------------------------------------------------------------------------------------------|" << endl;
		cout << "| ASDADASD    | Bachelor of Chemical Engineering Technology(Environment) with Honours            | APPROVED     |" << endl;
		cout << "=================================================================================================================" << endl;

*/