#ifndef ARROWKEYSELECTION_H
#define ARROWKEYSELECTION_H

using namespace std;

class arrowKeySelection {
	public:
		void color(int color);
		void gotoxy(int x, int y);
		int mainMenuSelection();
		int loginSelection();
};

#endif 

