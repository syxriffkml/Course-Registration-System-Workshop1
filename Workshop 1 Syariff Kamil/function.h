#ifndef FUNCTION_H
#define FUNCTION_H

using namespace std;

class function {
	public:
		static void ConnectionFunction();
		void WriteInColor(unsigned short,string);
		void mainMenu();
		void registration();
		int studentLogin();
		void studentMenu();
		int adminLogin();
		void adminMenu();
};

#endif 
