#include <iostream>
#include <fstream> //text file (mainly for interface)
#include <cstdlib> //standard library
#include <conio.h> //using getch
#include <windows.h> //windows library (WARNING : ONLY WORKS IN WINDOWS)
#include <string>
#include <mysql.h>
#include "function.h" // functions header
#include "arrowKeySelection.h" // menu arrow keys selection function header

#include <limits> //just for error(when user input alphabet and numbers) -  cin.ignore(numeric_limits<streamsize>::max(), '\n');
#undef max; //just for error(when user input alphabet and numbers) -   cin.ignore(numeric_limits<streamsize>::max(), '\n');

using namespace std;

int main() {
    //fixed console size   
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r); //stores the console's current dimensions
    MoveWindow(console, r.left, r.top, 870, 800, TRUE); // 870 width, 800 height
    system("color 0f"); //0-black bg, f- white text
    //end of fixed console size

    // Call Methods
    function::ConnectionFunction();
    // Call Methods End

    function f;
    arrowKeySelection arrowKey;
    int selection = 0, loginType = 0, studentSelection = 0;
    int count = 0, backToStudentMenu=0;
    char choice;

    start:
    f.mainMenu();
    selection=arrowKey.mainMenuSelection(); // 1. login selection(student or admin), 2. Register, 3. Exit 
    if (selection == 1) { //LOGIN PAGE
        f.mainMenu();
        loginType = arrowKey.loginSelection();
        if (loginType == 1) { //STUDENT LOGIN 
            count=f.studentLogin();
            if (count == 3) {
                goto start;
            }
            do {// STUDENT MENU LOOP

                f.studentMenu();
                studentSelection = arrowKey.studentPageSelection();
                if (studentSelection == 1) {
                    //function later on
                    cout << "Wanna go back to student menu ? press 8 for yes : ";
                    cin >> backToStudentMenu;
                }else if (studentSelection == 2) {
                    //function later on
                    cout << "Wanna go back to student menu ? press 8 for yes : ";
                    cin >> backToStudentMenu;
                }else if (studentSelection == 3) {
                    //function later on
                }else if (studentSelection == 8) { // "logout"
                    goto start;
                }


            } while (backToStudentMenu == 8);
        }
        else if (loginType == 2) { //ADMIN LOGIN (TABLE NOT CREATED YET SO CAN'T LOGIN)
            count = f.adminLogin();
            if (count == 3) {
                goto start;
            }
            f.adminMenu();
        }
    }
    else if (selection == 2) { // REGISTER
        f.registration();
        goto start;
    }
    else if (selection == 3) {// EXIT
        return 0;
    }

    return 0;
}
