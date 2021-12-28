#ifndef ARROWKEYSELECTION_H
#define ARROWKEYSELECTION_H

using namespace std;

class arrowKeySelection {
	public:
		void color(int color);
		void gotoxy(int x, int y);
		int mainMenuSelection();
		int loginSelection();
		int studentPageSelection();
		int maleOrFemale();
		int maritalStatusSelection();
		int eduLevelSelection();
		int resetOrProceed(int& check);
		int editStuDetailSelection();
		int facultySelection(int& check);
		int adminPageSelection();
		int adminGraphSelection();
		int adminStudentListSelection();
};

#endif 

