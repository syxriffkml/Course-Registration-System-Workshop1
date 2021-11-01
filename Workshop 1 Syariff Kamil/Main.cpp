#include <iostream>
#include <fstream> //text file (mainly for interface)
#include <cstdlib> //standard library
#include <conio.h> //using getch
#include <windows.h> //windows library
#include <limits> //just for error(when user input alphabet and numbers) -  cin.ignore(numeric_limits<streamsize>::max(), '\n');
#undef max; //just for error(when user input alphabet and numbers) -   cin.ignore(numeric_limits<streamsize>::max(), '\n');
#include <string>
#include <mysql.h>
#include "function.h" // functions
#include "menuSelection.h" // menu arrow keys selection function header

using namespace std;

int main() {
    //fixed console size   
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r); //stores the console's current dimensions
    MoveWindow(console, r.left, r.top, 870, 800, TRUE); // 870 width, 800 height (only looks good on 24 inch monitor)
    //end of fixed console size

    // Call Methods
    function::ConnectionFunction();
    // Call Methods End

    function f;
    menuSelection select;
    int selection = 0,count = 0;
    char choice;

    cout << endl << ifstream("interface/Homepage.txt").rdbuf() << endl;
    selection = select.mainMenu();
    if (selection == 1) {
        count = f.studentLogin();
        if (count == 3) {
            main();
        }
        else if (count < 3) {
            f.studentMenu();
        }
    }
    else if (selection == 2) {
        choice = f.registration();
        if (choice == 'y' || choice == 'Y') {
            f.studentLogin();
        }
        else {
            main();
        }
    }
    else if (selection == 3) {
        return 0;
    }

    return 0;
}
