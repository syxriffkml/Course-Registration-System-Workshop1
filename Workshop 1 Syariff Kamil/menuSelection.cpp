#include <iostream>
#include <windows.h>
#include <conio.h>
#include <fstream> //text file (mainly for interface)
#include "menuSelection.h" // menu arrow keys selection function header

using namespace std;

void menuSelection::color(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void menuSelection::gotoxy(int x, int y) {
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

int menuSelection::mainMenu() {

    int Set[] = { 7,12,7 }; // DEFAULT COLORS
    int counter = 2;
    char key;

    for (int i = 0;;) {
        gotoxy(5, 35);
        color(Set[0]);
        cout << "1. Login";

        gotoxy(16, 35);
        color(Set[1]);
        cout << "2. Register";

        gotoxy(30, 35);
        color(Set[2]);
        cout << "3. Exit";

        key = _getch();
        if (key == 75 && (counter >= 2 && counter <= 3)) { counter--; } //75 for arrow left key
        if (key == 77 && (counter >= 1 && counter <= 2)) { counter++; }  //77 for arrow right key

        if (key == '\r')//carriage return
        {   // if enter is click and highlight is on 1 the program will run the code here
            if (counter == 1) { 
                break;
            }
            if (counter == 2) { 
                break;
            }
            if (counter == 3) { 
                break;
            }
        }
        //default white
        Set[0] = 7;
        Set[1] = 7;
        Set[2] = 7;

        //set colours during selection
        if (counter == 1) { Set[0] = 12; }
        if (counter == 2) { Set[1] = 12; }
        if (counter == 3) { Set[2] = 12; }
    }

    if (counter == 1) {
        system("cls");
        return counter;
    }
    else if (counter == 2) {
        system("cls");
        return counter;
    }
    else if (counter == 3) {
        return counter;
    }
}
