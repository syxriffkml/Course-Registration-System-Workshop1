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
#include "arrowKeySelection.h" // menu arrow keys selection function header

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
    int selection = 0,count = 0;
    char choice;

    f.mainMenu(selection);
    if (selection == 1) {
        selection=arrowKey.loginSelection();
        if (selection == 1) {
            f.studentLogin();
            f.studentMenu();
        }
        else if (selection == 2) {
            f.adminMenu();
        }
    }
    else if (selection == 2) {
        f.registration();
        main();
    }
    else if (selection == 3) {
        return 0;
    }


    return 0;
}
