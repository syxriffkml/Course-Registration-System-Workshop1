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

//Global Variable
int qstate;
MYSQL* conn;
MYSQL_ROW row;
MYSQL_RES* res;
// Global Variable End

string stuID;

//Start of database connection function
void function::ConnectionFunction() {
    conn = mysql_init(0);
    if (conn) {
        cout << "Database Connected" << endl;
        cout << "Press any key to continue..." << endl;
        //getch();
        system("cls");
    }
    else {
        cout << "Failed To Connect!" << mysql_errno(conn) << endl;
    }

    conn = mysql_real_connect(conn, "localhost", "root", "", "courseadmission", 3306, NULL, 0);
    if (conn) {
        cout << "Database Connected To MySql" << conn << endl;
        cout << "Press any key to continue..." << endl;
        //getch();
        system("cls");
    }
    else {
        cout << "Failed To Connect!" << mysql_errno(conn) << endl;
    }
}
//End of database connection function


void function::mainMenu(int& selection) {

    arrowKeySelection arrowKey;


    cout << "========================================================================" << endl;
    cout << "                         COURSE ADMISSION SYSTEM                        " << endl;
    cout << "                               -MAIN MENU-                              " << endl;
    cout << "========================================================================" << endl;
    selection = arrowKey.mainMenuSelection(); //return 1. login selection(student or admin), 2. Register, 3. Exit
    
}


//Start of student register function
char function::registration() {

    string username, ic_num, gender, email, password;

    cout << "========================================================================" << endl;
    cout << "                           STUDENT REGISTRATION                         " << endl;
    cout << "========================================================================" << endl;
    cout << "Enter username : ";
    cin.ignore();
    getline(cin, username);

    cout << "Enter IC number ( without - ) : ";
    cin >> ic_num;

    cout << "Enter gender (Male or Female) : ";
    cin.ignore();
    getline(cin, gender);

    cout << "Enter email : ";
    getline(cin, email);

    cout << "Enter password : ";
    getline(cin, password);


    string checkIC_numQuerry = "select * from student where ic_num = '" + ic_num + "'";
    const char* checkIC_num = checkIC_numQuerry.c_str();
    qstate = mysql_query(conn, checkIC_num);
    if (!qstate) {

        res = mysql_store_result(conn);
        if (res->row_count == 1) {

            cout << "IC number already exists. Press Enter to Try Again...\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            system("pause");
            system("cls");
            registration();
        }
        else {

            string insertStudentRegisterQuery = "insert into student (username, ic_num, gender, email, password) values ('" + username + "', '" + ic_num + "', '" + gender + "', '" + email + "', '" + password + "')";
            const char* insertStudentRegister = insertStudentRegisterQuery.c_str();
            qstate = mysql_query(conn, insertStudentRegister);

            if (!qstate) {

                char c;
                cout << endl << "You have been registered. Do you want to log in? (y/n): ";
                cin >> c;
                if (c == 'y' || c == 'Y')
                    studentLogin();
                else
                    return c;
            }
            else {
                cout << "Query Execution Problem! MySQL Error #" << mysql_errno(conn) << endl;
            }
        }
    }
    else {
        cout << "Query Execution Problem! MySQL Error #" << mysql_errno(conn) << endl;
    }
}
//End of student register function


//Start of student login function
int function::studentLogin() {
    
    int count = 0;
    student_login:
    string ic_num, password = "";
    char ch;

    cout << "========================================================================" << endl;
    cout << "                              STUDENT LOGIN                             " << endl;
    cout << "========================================================================" << endl;
    cout << "Enter IC number ( without - ) : ";
    cin >> ic_num;

    cout << "Enter password : ";
    while (ch = _getch()) { //assign ASCII value to ch
        if (ch == 13) {  //13 is ENTER key in ASCII

            string studentLoginQuerry = "select * from student where ic_num = '" + ic_num + "' and password = '" + password + "'";
            const char* stuLogin = studentLoginQuerry.c_str();
            qstate = mysql_query(conn, stuLogin);

            if (!qstate) {
                res = mysql_store_result(conn);
                if (res->row_count == 1){ //Able to login :)
                    while (row = mysql_fetch_row(res)) {
                        stuID = row[0]; //ibarat $_SESSION dalam php la gitu
                    }
                    system("cls");
                    cout << endl << ifstream("interface/CorrectLogin.txt").rdbuf() << endl << endl << endl << endl;
                    system("pause");
                    system("cls");
                    return count=0;
                }
                else { //Unable to login :(
                    ic_num = "";
                    password = "";
                    count++;
                    if (count == 3) { //if student unable to login 3 times, the program will go back to main()
                        system("cls");
                        Beep(1000, 500);
                        cout << "ERROR, INCORRECT IC NUMBER/PASSWORD" << endl;
                        cout << endl << ifstream("interface/ErrorLogin.txt").rdbuf() << endl << endl << endl << endl;
                        system("pause");
                        system("cls");
                        return count;
                    }
                    else { //if student unable to login, the program will go back to login page again()
                        system("cls");
                        Beep(1000, 500);
                        cout << "ERROR, INCORRECT IC NUMBER/PASSWORD" << endl;
                        cout << endl << ifstream("interface/ErrorLogin.txt").rdbuf() << endl << endl << endl << endl;
                        system("pause");
                        system("cls");
                        goto student_login;
                    }
                }
            }
            else {
                cout << "Query Execution Problem! MySQL Error #" << mysql_errno(conn) << endl;
            }
        }
        else if (ch == 8) { //8 is BACKSPACE key in ASCII
            if (password.length() > 0) { //set condition blocking error while input
                cout << "\b \b"; //delete * everytime user click backspace
                password.erase(password.length() - 1); //erase string length
            }
        }
        else {
            //make password cannot be seen, when input it display as pasword : ************
            cout << "*";
            password += ch;
        }
    }
}
//End of student login function


void function::studentMenu() {

    cout << "========================================================================" << endl;
    cout << "                              STUDENT MENU                             " << endl;
    cout << "========================================================================" << endl;
    cout << "STUDENT PUNYA MENU" << endl;
}

void function::adminMenu() {
    
    cout << "========================================================================" << endl;
    cout << "                               ADMIN LOGIN                              " << endl;
    cout << "========================================================================" << endl;
    cout << "ADMIN PUNYA MENU" << endl;
}
