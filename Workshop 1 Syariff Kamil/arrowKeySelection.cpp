#include <iostream>
#include<sstream>
#include <windows.h>
#include <conio.h> //_getch()
#include <iomanip> //setw()
#include <fstream> //text file (mainly for interface)
#include "arrowKeySelection.h" // menu arrow keys selection function header

using namespace std;

void arrowKeySelection::color(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void arrowKeySelection::gotoxy(int x, int y) {
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

int arrowKeySelection::mainMenuSelection() {

    int Set[] = { 7,12,7 }; // DEFAULT COLORS
    int counter = 2;
    char key;

    for (int i = 0;;) {
        gotoxy(32, 9);
        color(Set[0]);
        cout << "1. Login";

        gotoxy(32, 11);
        color(Set[1]);
        cout << "2. Register";

        gotoxy(32, 13);
        color(Set[2]);
        cout << "3. Exit";

        key = _getch();
        if (key == 72 && (counter >= 2 && counter <= 3)) { counter--; } //72 for arrow up key
        if (key == 80 && (counter >= 1 && counter <= 2)) { counter++; }  //80 for arrow down key

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
        system("color 0f"); //when exit, the output text will be white
        return counter;
    }
}

int arrowKeySelection::loginSelection() {
    
    int Set[] = { 12,7 }; // DEFAULT COLORS
    int counter = 1;
    char key;

    cout << "\n\n" << setw(47) << "-SELECT LOGIN TYPE-" << endl;
    gotoxy(17, 13);
    cout << "(";

    gotoxy(57, 13);
    cout << ")";

    for (int i = 0;;) {
        gotoxy(19, 13);
        color(Set[0]);
        cout << "1. Student Login";

        gotoxy(42, 13);
        color(Set[1]);
        cout << "2. Admin Login";

        key = _getch();
        if (key == 75 && (counter >= 2 && counter <= 2)) { counter--; } //75 for arrow left key
        if (key == 77 && (counter >= 1 && counter <= 1)) { counter++; }  //77 for arrow right key

        if (key == '\r')//carriage return
        {   // if enter is click and highlight is on 1 the program will run the code here
            if (counter == 1) {
                break;
            }
            if (counter == 2) {
                break;    
            }
        }
        //default white
        Set[0] = 7;
        Set[1] = 7;

        //set colours during selection
        if (counter == 1) { Set[0] = 12; }
        if (counter == 2) { Set[1] = 12; }
    }

    if (counter == 1) {
        system("cls");
        return counter;
    }
    else if (counter == 2) {
        system("cls");
        system("color 0f");
        return counter;
    }
}

int arrowKeySelection::studentPageSelection() {

    int Set[] = { 12,7,7,7,7,7,7,7 }; // DEFAULT COLORS
    int counter = 1;
    char key;

    for (int i = 0;;) {

        gotoxy(32, 9);
        color(Set[0]);
        cout << "1. View Available Courses";

        gotoxy(32, 11);
        color(Set[1]);
        cout << "2. Insert Personal Details";

        gotoxy(32, 13);
        color(Set[2]);
        cout << "3. View or Edit Personal Details";

        gotoxy(32, 15);
        color(Set[3]);
        cout << "4. Insert Past Result";

        gotoxy(32, 17);
        color(Set[4]);
        cout << "5. Course Application";

        gotoxy(32, 19);
        color(Set[5]);
        cout << "6. View Application";

        gotoxy(32, 21);
        color(Set[6]);
        cout << "7. View Application Result";

        gotoxy(32, 23);
        color(Set[7]);
        cout << "8. Logout";

        key = _getch();
        if (key == 72 && (counter >= 2 && counter <= 8)) { counter--; } //72 for arrow up key
        if (key == 80 && (counter >= 1 && counter <= 7)) { counter++; }  //80 for arrow down key

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
            if (counter == 4) {
                break;
            }
            if (counter == 5) {
                break;
            }
            if (counter == 6) {
                break;
            }
            if (counter == 7) {
                break;
            }
            if (counter == 8) {
                break;
            }
        }
        //default white
        Set[0] = 7;
        Set[1] = 7;
        Set[2] = 7;
        Set[3] = 7;
        Set[4] = 7;
        Set[5] = 7;
        Set[6] = 7;
        Set[7] = 7;

        //set colours during selection
        if (counter == 1) { Set[0] = 12; }
        if (counter == 2) { Set[1] = 12; }
        if (counter == 3) { Set[2] = 12; }
        if (counter == 4) { Set[3] = 12; }
        if (counter == 5) { Set[4] = 12; }
        if (counter == 6) { Set[5] = 12; }
        if (counter == 7) { Set[6] = 12; }
        if (counter == 8) { Set[7] = 12; }
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
        system("cls");
        return counter;
    }
    else if (counter == 4) {
        system("cls");
        return counter;
    }
    else if (counter == 5) {
        system("cls");
        return counter;
    }
    else if (counter == 6) {
        system("cls");
        return counter;
    }
    else if (counter == 7) {
        system("cls");
        return counter;
    }
    else if (counter == 8) {
        system("cls");
        system("color 0f");
        return counter;
    }
}

int arrowKeySelection::maritalStatusSelection() {

    int Set[] = { 12,7,7,7 }; // DEFAULT COLORS
    int counter = 1;
    char key;

    for (int i = 0;;) {
        gotoxy(25, 16);
        color(Set[0]);
        cout << "1. Single";

        gotoxy(37, 16);
        color(Set[1]);
        cout << "2. Married";

        gotoxy(50, 16);
        color(Set[2]);
        cout << "3. Widowed";

        gotoxy(63, 16);
        color(Set[3]);
        cout << "4. Divorce";

        key = _getch();
        if (key == 75 && (counter >= 2 && counter <= 4)) { counter--; } //75 for arrow left key
        if (key == 77 && (counter >= 1 && counter <= 3)) { counter++; }  //77 for arrow right key

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
            if (counter == 4) {
                break;
            }
        }
        //default white
        Set[0] = 7;
        Set[1] = 7;
        Set[2] = 7;
        Set[3] = 7;

        //set colours during selection
        if (counter == 1) { Set[0] = 12; }
        if (counter == 2) { Set[1] = 12; }
        if (counter == 3) { Set[2] = 12; }
        if (counter == 4) { Set[3] = 12; }
    }

    if (counter == 1) {
        return counter;
    }
    else if (counter == 2) {
        return counter;
    }
    else if (counter == 3) {
        return counter;
    }
    else if (counter == 4) {
        return counter;
    }
}

int arrowKeySelection::eduLevelSelection() {

    int Set[] = { 12,7,7,7,7 }; // DEFAULT COLORS
    int counter = 1;
    char key;

    for (int i = 0;;) {
        gotoxy(31, 18);
        color(Set[0]);
        cout << "1. Diploma";

        gotoxy(44, 18);
        color(Set[1]);
        cout << "2. STPM";

        gotoxy(54, 18);
        color(Set[2]);
        cout << "3. Matriculation";

        gotoxy(73, 18);
        color(Set[3]);
        cout << "4. Foundation";

        gotoxy(89, 18);
        color(Set[4]);
        cout << "5. A-Level";

        key = _getch();
        if (key == 75 && (counter >= 2 && counter <= 5)) { counter--; } //75 for arrow left key
        if (key == 77 && (counter >= 1 && counter <= 4)) { counter++; }  //77 for arrow right key

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
            if (counter == 4) {
                break;
            }
            if (counter == 5) {
                break;
            }
        }
        //default white
        Set[0] = 7;
        Set[1] = 7;
        Set[2] = 7;
        Set[3] = 7;
        Set[4] = 7;

        //set colours during selection
        if (counter == 1) { Set[0] = 12; }
        if (counter == 2) { Set[1] = 12; }
        if (counter == 3) { Set[2] = 12; }
        if (counter == 4) { Set[3] = 12; }
        if (counter == 5) { Set[4] = 12; }
    }

    if (counter == 1) {
        return counter;
    }
    else if (counter == 2) {
        return counter;
    }
    else if (counter == 3) {
        return counter;
    }
    else if (counter == 4) {
        return counter;
    }
    else if (counter == 5) {
        return counter;
    }
}


//PENTINGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG
int arrowKeySelection::resetOrProceed(int& check) {

    int Set[] = { 7,12 }; // DEFAULT COLORS
    int counter = 2;
    char key;

    for (int i = 0;;) {

        if (check == 1) { //check 1 for add student details
            gotoxy(26, 26);
            color(Set[0]);
            cout << "1. Reset";

            gotoxy(42, 26);
            color(Set[1]);
            cout << "2. Proceed";
        }
        if (check == 2) { //check 2 for edit student details
            gotoxy(26, 32);
            color(Set[0]);
            cout << "1. Reset";

            gotoxy(42, 32);
            color(Set[1]);
            cout << "2. Proceed";
        }
        
        key = _getch();
        if (key == 75 && (counter >= 2 && counter <= 2)) { counter--; } //72 for arrow left key
        if (key == 77 && (counter >= 1 && counter <= 1)) { counter++; }  //80 for arrow right key

        if (key == '\r')//carriage return
        {   // if enter is click and highlight is on 1 the program will run the code here
            if (counter == 1) {
                break;
            }
            if (counter == 2) {
                break;
            }
        }
        //default white
        Set[0] = 7;
        Set[1] = 7;

        //set colours during selection
        if (counter == 1) { Set[0] = 12; }
        if (counter == 2) { Set[1] = 12; }
    }

    if (counter == 1) {
        return counter;
    }
    else if (counter == 2) {
        return counter;
    }
}
//PENTINGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG

int arrowKeySelection::editStuDetailSelection() {

    int Set[] = { 7,12 }; // DEFAULT COLORS
    int counter = 2;
    char key;

    for (int i = 0;;) {
        gotoxy(26, 39);
        color(Set[0]);
        cout << "1. Back";

        gotoxy(42, 39);
        color(Set[1]);
        cout << "2. Edit";

        key = _getch();
        if (key == 75 && (counter >= 2 && counter <= 2)) { counter--; } //72 for arrow left key
        if (key == 77 && (counter >= 1 && counter <= 1)) { counter++; }  //80 for arrow right key

        if (key == '\r')//carriage return
        {   // if enter is click and highlight is on 1 the program will run the code here
            if (counter == 1) {
                break;
            }
            if (counter == 2) {
                break;
            }
        }
        //default white
        Set[0] = 7;
        Set[1] = 7;

        //set colours during selection
        if (counter == 1) { Set[0] = 12; }
        if (counter == 2) { Set[1] = 12; }
    }

    if (counter == 1) {
        return counter;
    }
    else if (counter == 2) {
        return counter;
    }
}