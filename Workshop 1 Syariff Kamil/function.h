#ifndef FUNCTION_H
#define FUNCTION_H

using namespace std;

class function {
	public:
		static void ConnectionFunction();
		void WriteInColor(unsigned short,string);
		void mainMenu(int&);
		void registration();
		int studentLogin();
		void studentMenu();
		void adminMenu();
};

#endif 
