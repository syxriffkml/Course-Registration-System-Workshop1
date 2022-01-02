#include <iostream>
#include <sstream>
#include <cstdlib> //standard library
#include <conio.h> //using getch
#include <windows.h> //windows library (WARNING : ONLY WORKS IN WINDOWS)
#include <string>
#include <iomanip>
#include <mysql.h>
#include "function.h" // functions header
#include "arrowKeySelection.h" // menu arrow keys selection function header

//buang later kalau tak pakai
#include <limits> //just for error(when user input alphabet and numbers) -  cin.ignore(numeric_limits<streamsize>::max(), '\n');
#undef max; //just for error(when user input alphabet and numbers) -   cin.ignore(numeric_limits<streamsize>::max(), '\n');

using namespace std;

extern int qstate;
extern MYSQL* conn;
extern MYSQL_ROW row;
extern MYSQL_RES* res;

extern string stuID, username, subjectID, adminID, adminUser;


int main() {
    //fixed console size   
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
                
                string c1,c2,c3;
                string checkQ = "SELECT EXISTS(select * from studentdetails where studentdetails.student_id= '" + stuID + "')";
                const char* checkQuery = checkQ.c_str();
                qstate = mysql_query(conn, checkQuery);
                if (!qstate) {
                    res = mysql_store_result(conn);
                    if (res->row_count == 1) {
                        while (row = mysql_fetch_row(res)) {
                            c1 = row[0];
                        }
                    }
                    if (c1 == "0") {
                        f.studentDetail();
                        backToStudentMenu = 1;
                        system("cls");
                    }
                    else if (c1 == "1") {
                        string checkQ = "SELECT EXISTS(select * from result where result.student_id= '" + stuID + "')";
                        const char* checkQuery = checkQ.c_str();
                        qstate = mysql_query(conn, checkQuery);
                        if (!qstate) {
                            res = mysql_store_result(conn);
                            if (res->row_count == 1) {
                                while (row = mysql_fetch_row(res)) {
                                    c2 = row[0];
                                }
                            }
                            if (c2 == "0") {
                                f.addGrades();
                                backToStudentMenu = 1;
                                system("cls");
                            }
                            else if (c2 == "1") {
                                f.studentMenu();
                                studentSelection = arrowKey.studentPageSelection();

                                if (studentSelection == 1) {
                                    f.displayFacultyAndCourses();
                                    cout << "\nPress 1 to go back to student menu : ";
                                    cin >> backToStudentMenu;
                                    system("cls");
                                }
                                else if (studentSelection == 2) { // view and edit personal details
                                    f.editStudentDisplay();
                                    cout << "\nPress 1 to go back to student menu : ";
                                    cin >> backToStudentMenu;
                                    system("cls");
                                }
                                else if (studentSelection == 3) { // apply 3 courses
                                    string checkQ = "SELECT EXISTS(select * from application where application.student_id= '" + stuID + "')";
                                    const char* checkQuery = checkQ.c_str();
                                    qstate = mysql_query(conn, checkQuery);
                                    if (!qstate) {
                                        res = mysql_store_result(conn);
                                        if (res->row_count == 1) {
                                            while (row = mysql_fetch_row(res)) {
                                                c3 = row[0];
                                            }
                                        }
                                    }
                                    if (c3 == "0") {
                                        f.application();
                                        cout << "\nPress 1 to go back to student menu : ";
                                        cin >> backToStudentMenu;
                                        system("cls");
                                    }
                                    else {
                                        f.applicationMenu();
                                        cout << setw(62) << "YOU HAVE MADE AN APPLICATION" << endl;
                                        cout << "\nPress 1 to go back to student menu : ";
                                        cin >> backToStudentMenu;
                                        system("cls");
                                    }
                                    
                                }
                                else if (studentSelection == 4) { // view application
                                    f.viewApplication();
                                    cout << "\nPress 1 to go back to student menu : ";
                                    cin >> backToStudentMenu;
                                    system("cls");
                                }
                                else if (studentSelection == 5) { // view application
                                    f.applicationResult();
                                    cout << "\nPress 1 to go back to student menu : ";
                                    cin >> backToStudentMenu;
                                    system("cls");
                                }
                                else if (studentSelection == 6) { // "logout"
                                    goto start;
                                }
                            }
                        }
                        else {
                            cout << "Query Execution Problem! MySQL Error #" << mysql_errno(conn) << endl;
                        }
                    }
                }
                else {
                    cout << "Query Execution Problem! MySQL Error #" << mysql_errno(conn) << endl;
                }
            } while (backToStudentMenu == 1);
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
                    cout << "\nPress 1 to go back to admin menu : ";
                    cin >> backToAdminMenu;
                    system("cls");
                }
                else if (adminSelection == 2) { //VIEW LIST OF STUDENT
                    f.adminViewStudentList();
                    cout << "\nPress 1 to go back to admin menu : ";
                    cin >> backToAdminMenu;
                    system("cls");
                }
                else if (adminSelection == 3) { //APPROVE STUDENT APPLICATION
                    f.adminApproval();
                    cout << "\nPress 1 to go back to admin menu : ";
                    cin >> backToAdminMenu;
                    system("cls");
                }
                else if (adminSelection == 5) { //"logout"
                    goto start;
                }
            } while (backToAdminMenu == 1);
            
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
