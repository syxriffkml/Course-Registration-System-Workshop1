#include <iostream>
#include <sstream>
#include <cstdlib> //standard library
#include <conio.h> //using getch
#include <windows.h> //windows library (WARNING : ONLY WORKS IN WINDOWS)
#include <string>
#include <mysql.h>
#include "function.h" // functions header
#include "arrowKeySelection.h" // menu arrow keys selection function header

//buang later kalau tak pakai
#include <limits> //just for error(when user input alphabet and numbers) -  cin.ignore(numeric_limits<streamsize>::max(), '\n');
#undef max; //just for error(when user input alphabet and numbers) -   cin.ignore(numeric_limits<streamsize>::max(), '\n');

using namespace std;

int main() {
    //fixed console size   
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r); //stores the console's current dimensions
    MoveWindow(console, r.left, r.top, 1100, 700, TRUE); // 870 width, 800 height
    system("color 0f"); //0-black bg, f- white text
    //end of fixed console size

    // Call Methods
    function::ConnectionFunction();
    // Call Methods End

    function f;
    arrowKeySelection arrowKey;
    int selection = 0, loginType = 0, studentSelection = 0, adminSelection = 0;
    int count = 0, backToStudentMenu=0, backToAdminMenu=0;
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
                    f.displayFacultyAndCourses();
                    cout << "\nPress 8 to go back to student menu : ";
                    cin >> backToStudentMenu;
                    system("cls");
                }else if (studentSelection == 2) { //insert personal detail
                    f.studentDetail();
                    cout << "\nPress 8 to go back to student menu : ";
                    cin >> backToStudentMenu;
                    system("cls");
                }else if (studentSelection == 3) { // view and edit personal details
                    f.editStudentDisplay();
                    cout << "\nPress 8 to go back to student menu : ";
                    cin >> backToStudentMenu;
                    system("cls");
                }else if (studentSelection == 4) { // calculate cgpa
                    f.addGrades();
                    cout << "\nPress 8 to go back to student menu : ";
                    cin >> backToStudentMenu;
                    system("cls");
                }
                else if (studentSelection == 5) { // apply 3 courses
                    f.application();
                    cout << "\nPress 8 to go back to student menu : ";
                    cin >> backToStudentMenu;
                    system("cls");
                }
                else if (studentSelection == 6) { // view application
                    f.viewApplication();
                    cout << "\nPress 8 to go back to student menu : ";
                    cin >> backToStudentMenu;
                    system("cls");
                }
                else if (studentSelection == 8) { // "logout"
                    goto start;
                }
            } while (backToStudentMenu == 8);
        }
        else if (loginType == 2) { //ADMIN LOGIN 
            count = f.adminLogin();
            if (count == 3) {
                goto start;
            }
            do {
                f.adminMenu();
                adminSelection = arrowKey.adminPageSelection();
                if (adminSelection == 1) { //VIEW GRAPHS
                    f.adminViewGraph();
                    cout << "\nPress 8 to go back to admin menu : ";
                    cin >> backToAdminMenu;
                    system("cls");
                }
                else if (adminSelection == 2) { //VIEW LIST OF STUDENT
                    f.adminViewStudentList();
                    cout << "\nPress 8 to go back to admin menu : ";
                    cin >> backToAdminMenu;
                    system("cls");
                }
                else if (adminSelection == 3) { //APPROVE STUDENT APPLICATION
                    f.adminApproval();
                    cout << "\nPress 8 to go back to admin menu : ";
                    cin >> backToAdminMenu;
                    system("cls");
                }
                else if (adminSelection == 5) { //"logout"
                    goto start;
                }
            } while (backToAdminMenu == 8);
            
        }
    }
    else if (selection == 2) { // REGISTRATION
        f.registration();
        goto start;
    }
    else if (selection == 3) {// EXIT
        return 0;
    }

    return 0;
}
