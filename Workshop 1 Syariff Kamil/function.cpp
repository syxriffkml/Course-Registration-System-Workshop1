﻿#include <iostream>
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
        cout << "Failed To Connect! MySQL Error #" << mysql_errno(conn) << endl;
    }
}
//End of database connection function


// start of change text colour
void function::WriteInColor(unsigned short color, string outputString)
{
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hcon, color);
    cout << outputString;
}
// end of change text colour


//start of main menu function
void function::mainMenu() {

    //arrowKeySelection arrowKey;

    cout << "========================================================================" << endl;
    cout << "                         COURSE ADMISSION SYSTEM                        " << endl;
    cout << "                               -MAIN MENU-                              " << endl;
    cout << "========================================================================" << endl;
    WriteInColor(11,"      +----------------------------------------------------------+\n"); //start here, the text color will be
    WriteInColor(11,"      | INSTRUCTION : Move arrow keys (Up, Down, Left, Right) to |\n");
    WriteInColor(11,"      | move the selection and press ENTER key to select         |\n");
    WriteInColor(11,"      +----------------------------------------------------------+\n");
    WriteInColor(7, " "); // change back the next text colour to white
    //selection = arrowKey.mainMenuSelection(); 
    
}
//end of main menu function



//Start of student register function
void function::registration() {

    string username, ic_num, gender, email, password;

    cout << "========================================================================" << endl;
    cout << "                           STUDENT REGISTRATION                         " << endl;
    cout << "========================================================================" << endl;
    cout << "Enter username : ";
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
                cout << endl << "You have successfully registered! ";
                system("pause");
                system("cls");
                return;
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
    string ic_num, password = "",studentPasswordDB;
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
                if (res->row_count == 1) { //
                    while (row = mysql_fetch_row(res)) {
                        stuID = row[0]; //ibarat $_SESSION dalam php la gitu (row[0] is row student id dalam database)
                        studentPasswordDB = row[5]; //row[5] for password
                    }
                }
                if (password == studentPasswordDB) {//password exaclty sama ngan database
                    system("cls");
                    cout << "CORRECT LOGIN!" << endl;
                    //cout << endl << ifstream("interface/CorrectLogin.txt").rdbuf() << endl << endl << endl << endl;
                    system("pause");
                    system("cls");
                    return count = 0;
                }
                else if (password != studentPasswordDB) {
                    ic_num = "";
                    password = "";
                    count++;
                    if (count == 3) { //if student unable to login 3 times, the program will go back to main()
                        system("cls");
                        Beep(1000, 500);
                        cout << "ERROR, INCORRECT IC NUMBER or PASSWORD\nYOU WILL GO BACK TO MAIN MENU" << endl;
                        //cout << endl << ifstream("interface/ErrorLogin.txt").rdbuf() << endl << endl << endl << endl;
                        system("pause");
                        system("cls");
                        return count;
                    }
                    else { //if student unable to login, the program will go back to login page again()
                        system("cls");
                        Beep(1000, 500);
                        cout << "ERROR, INCORRECT IC NUMBER or PASSWORD" << endl;
                        //cout << endl << ifstream("interface/ErrorLogin.txt").rdbuf() << endl << endl << endl << endl;
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


//start of student menu function
void function::studentMenu() {
    string username;
    string querry = "select username from student where student_id = '" + stuID + "'";
    const char* getUsername = querry.c_str();
    qstate = mysql_query(conn, getUsername);
    if (!qstate) {

        res = mysql_store_result(conn);
        if (res->row_count == 1) { //Able to login :)
            while (row = mysql_fetch_row(res)) {
                username = row[0]; //row[0] because we only select
            }
        }
        else {
            cout << "Query Execution Problem! MySQL Error #" << mysql_errno(conn) << endl;
        }
        cout << "========================================================================" << endl;
        cout << "Welcome, user ";
        WriteInColor(11, username + " " + stuID + "\n");//start here, the text color will be
        WriteInColor(7," "); // change back the next text colour to white
        cout << "                              STUDENT MENU                             " << endl;
        cout << "========================================================================" << endl;
        WriteInColor(11, "      +----------------------------------------------------------+\n"); //start here, the text color will be
        WriteInColor(11, "      | INSTRUCTION : Move arrow keys (Up, Down, Left, Right) to |\n");
        WriteInColor(11, "      | move the selection and press ENTER key to select         |\n");
        WriteInColor(11, "      +----------------------------------------------------------+\n");
        WriteInColor(7, " "); // change back the next text colour to white
    }
    else {
        cout << "Query Execution Problem! MySQL Error #" << mysql_errno(conn) << endl;
    }
    
}
//end of student menu function






//Start of admin login function (TABLE NOT CREATED YET)
int function::adminLogin() {

    int count = 0;
    admin_login:
    string ic_num, password = "", studentPasswordDB;
    char ch;

    cout << "========================================================================" << endl;
    cout << "                               ADMIN LOGIN                              " << endl;
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
                if (res->row_count == 1) { //
                    while (row = mysql_fetch_row(res)) {
                        stuID = row[0]; //ibarat $_SESSION dalam php la gitu (row[0] is row student id dalam database)
                        studentPasswordDB = row[5]; //row[5] for password
                    }
                }
                if (password == studentPasswordDB) {//password exaclty sama ngan database
                    system("cls");
                    cout << "CORRECT LOGIN!" << endl;
                    //cout << endl << ifstream("interface/CorrectLogin.txt").rdbuf() << endl << endl << endl << endl;
                    system("pause");
                    system("cls");
                    return count = 0;
                }
                else if (password != studentPasswordDB) {
                    ic_num = "";
                    password = "";
                    count++;
                    if (count == 3) { //if student unable to login 3 times, the program will go back to main()
                        system("cls");
                        Beep(1000, 500);
                        cout << "ERROR, INCORRECT IC NUMBER or PASSWORD\nYOU WILL GO BACK TO MAIN MENU" << endl;
                        //cout << endl << ifstream("interface/ErrorLogin.txt").rdbuf() << endl << endl << endl << endl;
                        system("pause");
                        system("cls");
                        return count;
                    }
                    else { //if student unable to login, the program will go back to login page again()
                        system("cls");
                        Beep(1000, 500);
                        cout << "ERROR, INCORRECT IC NUMBER or PASSWORD" << endl;
                        //cout << endl << ifstream("interface/ErrorLogin.txt").rdbuf() << endl << endl << endl << endl;
                        system("pause");
                        system("cls");
                        goto admin_login;
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
//End of admin login function (TABLE NOT CREATED YET)


//start of admin menu function
void function::adminMenu() {
    
    cout << "========================================================================" << endl;
    cout << "                               ADMIN LOGIN                              " << endl;
    cout << "========================================================================" << endl;
    cout << "ADMIN PUNYA MENU" << endl;
}
//end of admin menu function
