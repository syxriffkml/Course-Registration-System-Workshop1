#include <iostream>
#include <iomanip>
#include<sstream>
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

string stuID,username;

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
    WriteInColor(11, "      +----------------------------------------------------------+\n"); //start here, the text color will be
    WriteInColor(11, "      | INSTRUCTION : Move arrow keys (Up, Down, Left, Right) to |\n");
    WriteInColor(11, "      | move the selection and press ENTER key to select         |\n");
    WriteInColor(11, "      +----------------------------------------------------------+\n");
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
    cout << "\nEnter username : ";
    getline(cin, username);

    cout << "\nEnter IC number ( without - ) : ";
    cin >> ic_num;

    cout << "\nEnter gender (Male or Female) : ";
    cin.ignore();
    getline(cin, gender);

    cout << "\nEnter email : ";
    getline(cin, email);

    cout << "\nEnter password : ";
    getline(cin, password);


    string checkIC_numQuerry = "select * from student where ic_num = '" + ic_num + "'";
    const char* checkIC_num = checkIC_numQuerry.c_str();
    qstate = mysql_query(conn, checkIC_num);
    if (!qstate) {

        res = mysql_store_result(conn);
        if (res->row_count == 1) {

            cout << "\nIC number already exists. Press Enter to Try Again...\n";
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
    string ic_num, password = "", studentPasswordDB, studentICnum;
    char ch;

    cout << "========================================================================" << endl;
    cout << "                              STUDENT LOGIN                             " << endl;
    cout << "========================================================================" << endl;
    cout << "\nEnter IC number ( without - ) : ";
    cin >> ic_num;

    cout << "\nEnter password : ";
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
                        studentICnum = row[2];  //row[1] for ic number
                        studentPasswordDB = row[5]; //row[5] for password
                    }
                }
                if ((password == studentPasswordDB) && (ic_num == studentICnum)) {//password exaclty sama ngan database
                    system("cls");
                    cout << "CORRECT LOGIN!" << endl;
                    //cout << endl << ifstream("interface/CorrectLogin.txt").rdbuf() << endl << endl << endl << endl;
                    system("pause");
                    system("cls");
                    return count = 0;
                }
                else if ((password != studentPasswordDB) && (ic_num != studentICnum)) {
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
        cout << "( Welcome, user ";
        WriteInColor(11, username + " " + stuID);//start here, the text color will be
        WriteInColor(7, " )\n"); // change back the next text colour to white
        cout << "========================================================================" << endl;   
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


//Start of student insert details function
void function::studentDetail() {

    startStudentDetail:
    arrowKeySelection arrow;
    int maritalSelection = 0, eduSelection = 0, workExperience = 0, resetOrProceed = 0;
    string fullname, address, phoneNum, maritalStatus, eduLevel;

    cout << "( Welcome, user ";
    WriteInColor(11, username + " " + stuID);//start here, the text color will be
    WriteInColor(7, " )\n"); // change back the next text colour to white
    cout << "========================================================================" << endl;
    cout << "                              STUDENT MENU                              " << endl;
    cout << "                           -personal details-                           " << endl;
    cout << "========================================================================" << endl;
    WriteInColor(11, "      +----------------------------------------------------------+\n"); //start here, the text color will be
    WriteInColor(11, "      | INSTRUCTION : Move arrow keys (Up, Down, Left, Right) to |\n");
    WriteInColor(11, "      | move the selection and press ENTER key to select         |\n");
    WriteInColor(11, "      +----------------------------------------------------------+\n");
    WriteInColor(7, " "); // change back the next text colour to white

    cout << "\nEnter fullname : ";
    cin.ignore();
    getline(cin, fullname);

    cout << "\nEnter home address : ";
    getline(cin, address);

    cout << "\nEnter phone number ( without - ) : ";
    getline(cin, phoneNum);

    cout << "\nSelect martial_status : ";
    maritalSelection = arrow.maritalStatusSelection();
    if (maritalSelection == 1) {
        maritalStatus = "Single";
    }
    else if (maritalSelection == 2) {
        maritalStatus = "Married";
    }
    else if (maritalSelection == 3) {
        maritalStatus = "Widowed";
    }
    else if (maritalSelection == 4) {
        maritalStatus = "Divorce";
    }
    WriteInColor(7, " ");

    cout << "\n\nSelect past education level : ";
    eduSelection = arrow.eduLevelSelection();
    if (eduSelection == 1) {
        eduLevel = "Diploma";
    }
    else if (eduSelection == 2) {
        eduLevel = "STPM";
    }
    else if (eduSelection == 3) {
        eduLevel = "Matriculation";
    }
    else if (eduSelection == 4) {
        eduLevel = "Foundation";
    }
    else if (eduSelection == 5) {
        eduLevel = "A-Level";
    }
    WriteInColor(7, " ");

    cout << "\n\nEnter work experience in years ( enter 0 if none ) : ";
    cin >> workExperience;

    cout << "\n\n\n" << setw(51) << "DO YOU WANT TO PROCEED ?";
    resetOrProceed = arrow.resetOrProceed();
    WriteInColor(7, " ");
    if (resetOrProceed == 1) { //reset
        system("cls");
        goto startStudentDetail;
    }
    else if (resetOrProceed == 2) { //proceed 
    //change int to string
    stringstream streamWorkExp;
    string sWorkExp;
    streamWorkExp << workExperience;
    streamWorkExp >> sWorkExp;
    //change int to string

    string stuDetailQuery = "insert into studentdetails (student_id,fullname, home_address, phone_num, marital_status, education_level, work_experience) values ('"
        + stuID + "', '" + fullname + "', '" + address + "', '" + phoneNum + "', '" + maritalStatus + "', '" + eduLevel + "','" + sWorkExp + "')";
    const char* insertStudentDetail = stuDetailQuery.c_str();
    qstate = mysql_query(conn, insertStudentDetail);

    if (!qstate) {
        cout << endl << "\n\nYou have successfully entered your student details! ";
        system("pause");
        return;
    }
    else {
        cout << "Query Execution Problem! MySQL Error #" << mysql_errno(conn) << endl;
    }
    }
}
//End of student insert details function


void function::editStudentDisplay() {

    cout << "( Welcome, user ";
    WriteInColor(11, username + " " + stuID);//start here, the text color will be
    WriteInColor(7, " )\n"); // change back the next text colour to white
    cout << "========================================================================" << endl;
    cout << "                              STUDENT MENU                              " << endl;
    cout << "                           -personal details-                           " << endl;
    cout << "========================================================================" << endl;
    WriteInColor(11, "      +----------------------------------------------------------+\n"); //start here, the text color will be
    WriteInColor(11, "      | INSTRUCTION : Move arrow keys (Up, Down, Left, Right) to |\n");
    WriteInColor(11, "      | move the selection and press ENTER key to select         |\n");
    WriteInColor(11, "      +----------------------------------------------------------+\n");
    WriteInColor(7, " "); // change back the next text colour to white


}



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
