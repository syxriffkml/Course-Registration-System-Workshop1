#include <iostream>
#include <iomanip>
#include <sstream>
//#include <cstdlib> //standard library
#include <conio.h> //using getch
#include <windows.h> //windows library
#include <string>
#include <mysql.h>
#include "function.h" // functions
#include "arrowKeySelection.h" // menu arrow keys selection function header

#include <limits> //just for error(when user input alphabet and numbers) -  cin.ignore(numeric_limits<streamsize>::max(), '\n');
#undef max; //just for error(when user input alphabet and numbers) -   cin.ignore(numeric_limits<streamsize>::max(), '\n');

using namespace std;

//Global Variable
int qstate;
MYSQL* conn;
MYSQL_ROW row;
MYSQL_RES* res;

string stuID, username, subjectID, adminID, adminUser;
// Global Variable End



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
    WriteInColor(11, "      | INSTRUCTION : (1) Move arrow keys (Up, Down) to move the |\n");
    WriteInColor(11, "      | selection and press ENTER key to select                  |\n");
    WriteInColor(11, "      | (2) Running the programme in fullscreen is recommended ! |\n");
    WriteInColor(11, "      +----------------------------------------------------------+\n");
    WriteInColor(7, " "); // change back the next text colour to white
    //selection = arrowKey.mainMenuSelection(); 

}
//end of main menu function


//Start of student register function
void function::registration() {
    redoICNumber:
    arrowKeySelection arrow;
    string username, ic_num="", gender, email, password;
    int genderSelect, check = 1;

    cout << "========================================================================" << endl;
    cout << "                           STUDENT REGISTRATION                         " << endl;
    cout << "========================================================================" << endl;
    cout << "\nEnter username : ";
    getline(cin, username);


    cout << "\nEnter IC number ( without - ) : ";
    cin >> ic_num;
    if (ic_num.size() > 12) {
        cout << "You entered "; WriteInColor(12,"MORE THAN"); WriteInColor(7,""); cout << " 12 digits, IC number needs to have exactly 12 digits. Please re-enter your IC number." << endl << endl;
        cin.ignore();
        system("pause");
        system("cls");
        goto redoICNumber;
    }
    else if (ic_num.size() < 12) {
        cout << "You entered "; WriteInColor(12, "LESS THAN"); WriteInColor(7, ""); cout << " 12 digits, IC number needs to have exactly 12 digits. Please re-enter your IC number." << endl << endl;
        cin.ignore();
        system("pause");
        system("cls");
        goto redoICNumber;
    }
    
    //cout << "\nEnter IC number ( without - ) : ";
    //cin >> ic_num;

    cout << "\nEnter gender (Male or Female) : ";
    genderSelect = arrow.maleOrFemale(check);
    if (genderSelect == 1) {
        gender = "Male";
        check = 0;
    }
    else if (genderSelect == 2) {
        gender = "Female";
        check = 0;
    }
    WriteInColor(7, " ");

    cout << "\n\nEnter email : ";
    cin.ignore();
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
                        username = row[1];
                        studentICnum = row[2];  //row[1] for ic number
                        studentPasswordDB = row[5]; //row[5] for password
                    }
                }
                if ((password == studentPasswordDB) && (ic_num == studentICnum)) {//password exaclty sama ngan database
                    system("cls");
                    cout << "========================================================================" << endl;
                    cout << "                              STUDENT LOGIN                             " << endl;
                    cout << "========================================================================" << endl;
                    cout << "\nCORRECT LOGIN!" << endl;
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
                        cout << "========================================================================" << endl;
                        cout << "                              STUDENT LOGIN                             " << endl;
                        cout << "========================================================================" << endl;
                        cout << "\nERROR, INCORRECT IC NUMBER or PASSWORD\nYOU WILL GO BACK TO MAIN MENU" << endl;
                        //cout << endl << ifstream("interface/ErrorLogin.txt").rdbuf() << endl << endl << endl << endl;
                        system("pause");
                        system("cls");
                        return count;
                    }
                    else { //if student unable to login, the program will go back to login page again()
                        system("cls");
                        Beep(1000, 500);
                        cout << "========================================================================" << endl;
                        cout << "                              STUDENT LOGIN                             " << endl;
                        cout << "========================================================================" << endl;
                        cout << "\nERROR, INCORRECT IC NUMBER or PASSWORD" << endl;
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
        WriteInColor(11, username);//start here, the text color will be
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
        cout << "6Query Execution Problem! MySQL Error #" << mysql_errno(conn) << endl;
    }
}
//end of student menu function


//Start of student insert details function
void function::studentDetail() {

    startStudentDetail:
    arrowKeySelection arrow;
    int maritalSelection = 0, eduSelection = 0, workExperience = 0, resetOrProceed = 0, check = 1; //check 2 for add student detail 
    string fullname, address, phoneNum, maritalStatus, eduLevel;

    cout << "( Welcome, user ";
    WriteInColor(11, username);//start here, the text color will be
    WriteInColor(7, " )\n"); // change back the next text colour to white
    cout << "========================================================================" << endl;
    cout << "                              STUDENT MENU                              " << endl;
    cout << "                        -insert personal details-                       " << endl;
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
    eduSelection = arrow.eduLevelSelection(check);
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
    resetOrProceed = arrow.resetOrProceed(check);
    check = 0; //reset check
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
            cout << "7Query Execution Problem! MySQL Error #" << mysql_errno(conn) << endl;
        }
    }
}
//End of student insert details function


//Start of student view/edit details
void function::editStudentDisplay() {

    cin.ignore();
    viewDetail:
    arrowKeySelection arrow;
    int edit = 0;
    string cgpaResult;

    cout << "( Welcome, user ";
    WriteInColor(11, username);//start here, the text color will be
    WriteInColor(7, " )\n"); // change back the next text colour to white
    cout << "========================================================================" << endl;
    cout << "                              STUDENT MENU                              " << endl;
    cout << "                           -personal details-                           " << endl;
    cout << "========================================================================" << endl;
    WriteInColor(11, "      +----------------------------------------------------------+\n"); //start here, the text color will be
    WriteInColor(11, "      | INSTRUCTION :                                            |\n");
    WriteInColor(11, "      | (1) Move arrow keys (Up, Down, Left, Right) to move the  |\n");
    WriteInColor(11, "      | selection and press ENTER key to select                  |\n");
    WriteInColor(11, "      | (2) Only the details such as username, email, home       |\n");
    WriteInColor(11, "      | address, phone number & marital status can be change     |\n");
    WriteInColor(11, "      +----------------------------------------------------------+\n");
    WriteInColor(7, " "); // change back the next text colour to white

    string getCGPA = "select cgpa from result where semester = (SELECT MAX(semester) FROM result WHERE result.student_id= '" + stuID + "') AND result.student_id= '" + stuID + "'";
    const char* cgpa = getCGPA.c_str();
    qstate = mysql_query(conn, cgpa);
    if (!qstate) {
        res = mysql_store_result(conn);
        if (res->row_count == 1) {
            while (row = mysql_fetch_row(res)) {
                cgpaResult = row[0];
            }
        }
    }

    string stuDetailQuery = "select * from student,studentdetails where student.student_id ='" + stuID + "' AND studentdetails.student_id = '" + stuID + "'"; //from 2 tables
    const char* viewStudentDetail = stuDetailQuery.c_str();
    qstate = mysql_query(conn, viewStudentDetail);

    if (!qstate) {
        res = mysql_store_result(conn);
        if (res->row_count == 1) { 
            while (row = mysql_fetch_row(res)) {
                WriteInColor(7, "\n\n\n       Account Username : "); WriteInColor(11, row[1]);
                WriteInColor(7, "\n\n       IC Number : "); WriteInColor(11, row[2]);
                WriteInColor(7, "\n\n       Gender : "); WriteInColor(11, row[3]);
                WriteInColor(7, "\n\n       Email Address : "); WriteInColor(11, row[4]);
                WriteInColor(7, "\n\n       Full Name : "); WriteInColor(11, row[8]);
                WriteInColor(7, "\n\n       Home Address : "); WriteInColor(11, row[9]);
                WriteInColor(7, "\n\n       Phone Number : "); WriteInColor(11, row[10]);
                WriteInColor(7, "\n\n       Marital Status : "); WriteInColor(11, row[11]);
                WriteInColor(7, "\n\n       Education Level : "); WriteInColor(11, row[12]);
                WriteInColor(7, "\n\n       Work Experience : "); WriteInColor(11, row[13]);
                WriteInColor(7, "\n\n       Past CGPA : "); WriteInColor(11,""); cout << cgpaResult;
                WriteInColor(7, "\n"); // change back the next text colour to white

                
                cout << "\n\n\n" << setw(58) << "DO YOU WANT TO EDIT THE STUDENT DETAILS ?";
                edit = arrow.editStuDetailSelection();
                WriteInColor(7, " ");
                if (edit == 1) {
                    return; 
                }
                else if (edit == 2) {   
                    
                    system("cls");                   
                    editDetail:
                    int check = 2; //check 2 for edit student detail 
                    string newUsername, newEmail, newHomeAddress, newPhoneNum, newMaritalStatus;
                    cout << "( Welcome, user ";
                    WriteInColor(11, username);//start here, the text color will be
                    WriteInColor(7, " )\n"); // change back the next text colour to white
                    cout << "========================================================================" << endl;
                    cout << "                              STUDENT MENU                              " << endl;
                    cout << "                        -edit personal details-                         " << endl;
                    cout << "========================================================================" << endl;
                    
                    WriteInColor(7, "\n\n\n       Account Username : "); WriteInColor(11, row[1]);  WriteInColor(7, " ");
                    cout << "\n" << setw(26) << "Account Username : ";   
                    //cin.ignore();
                    getline(cin, newUsername);
                    
                    WriteInColor(7, "\n\n       Email Address : "); WriteInColor(11, row[4]);  WriteInColor(7, " ");
                    cout << "\n" << setw(23) << "Email Address : "; 
                    getline(cin, newEmail);

                    WriteInColor(7, "\n\n       Home Address : "); WriteInColor(11, row[9]);  WriteInColor(7, " ");
                    cout << "\n" << setw(22) << "Home Address : "; 
                    getline(cin, newHomeAddress);

                    WriteInColor(7, "\n\n       Phone Number : "); WriteInColor(11, row[10]); WriteInColor(7, " ");
                    cout << "\n" << setw(22) << "Phone Number : "; 
                    getline(cin, newPhoneNum);

                    WriteInColor(7, "\n\n       Marital Status : "); WriteInColor(11, row[11]); WriteInColor(7, " ");
                    cout << "\n" << setw(24) << "Marital Status : "; 
                    getline(cin, newMaritalStatus);
                    WriteInColor(7, "\n"); // change back the next text colour to white

                    cout << "\n\n\n" << setw(51) << "DO YOU WANT TO PROCEED ?";
                    int resetOrProceed = arrow.resetOrProceed(check); //align text
                    check = 0; //reset check
                    WriteInColor(7, " ");

                    if (resetOrProceed == 1) { //reset
                        system("cls");
                        goto editDetail; 
                    }
                    else if (resetOrProceed == 2) { //proceed edit
                        username = newUsername;
                        string updateDetailquery = "update student,studentdetails set student.username = '" + newUsername + "', student.email = '"
                            + newEmail + "', studentdetails.home_address = '" + newHomeAddress + "', studentdetails.phone_num = '" 
                            + newPhoneNum + "', studentdetails.marital_status = '" + newMaritalStatus + "' where student.student_id ='" 
                            + stuID + "' AND studentdetails.student_id = '" + stuID + "'";
                        const char* q = updateDetailquery.c_str();
                        qstate = mysql_query(conn, q);
                        if (!qstate)
                        {
                            cout << "\n\nYour student details are successfully updated" << endl << endl;
                            system("pause");
                            system("cls");
                            goto viewDetail;
                        }
                        else
                        {
                            cout << "Update Failed! MySQL Error #" << mysql_errno(conn) << endl;
                        }
                    }
                }
            }
        }
    }
    else {
        cout << "8Query Execution Problem! MySQL Error #" << mysql_errno(conn) << endl;
    }
}
//End of student view/edit details


//Start of Displaying list of Faculty and Courses (Student)
void function::displayFacultyAndCourses() {

    arrowKeySelection arrow;
    int facultyselect = 0,check = 1; //check = 2 for application

    cout << "( Welcome, user ";
    WriteInColor(11, username);//start here, the text color will be
    WriteInColor(7, " )\n"); // change back the next text colour to white
    cout << "=======================================================================================================" << endl;
    cout << "                                               STUDENT MENU                                            " << endl;
    cout << "                                            -list of faculties-                                        " << endl;
    cout << "=======================================================================================================" << endl;
    WriteInColor(11, "                       +----------------------------------------------------------+\n"); //start here, the text color will be
    WriteInColor(11, "                       | INSTRUCTION :                                            |\n");
    WriteInColor(11, "                       | Move arrow keys (Up, Down, Left, Right) to move the      |\n");
    WriteInColor(11, "                       | selection and press ENTER key to select                  |\n");
    WriteInColor(11, "                       +----------------------------------------------------------+\n");
    WriteInColor(7, ""); // change back the next text colour to white


    facultyselect = arrow.facultySelection(check); //arrow selection faculty, then cls
    string fs = to_string(facultyselect); // change int to string
    check = 0; //reset check

    cout << "( Welcome, user ";
    WriteInColor(11, username);//start here, the text color will be
    WriteInColor(7, " )\n"); // change back the next text colour to white
    cout << "=======================================================================================================" << endl;
    cout << "                                               STUDENT MENU                                            " << endl;
    cout << "                                             -list of courses-                                         " << endl;
    cout << "=======================================================================================================" << endl << endl;

    WriteInColor(11, "                       +----------------------------------------------------------+\n"); //start here, the text color will be
    WriteInColor(11, "                       | INFO :                                                   |\n");
    WriteInColor(11, "                       | Student's CGPA below the required CGPA will have their   |\n");
    WriteInColor(11, "                       | CGPA and work experience checked to see if they are      |\n");
    WriteInColor(11, "                       | eligible for the minimum requirements                    |\n");
    WriteInColor(11, "                       +----------------------------------------------------------+\n");
    WriteInColor(7, "\n\n"); // change back the next text colour to white

    string facultyQuery = "select * from courses where faculty_id = '" + fs + "'";
    const char* fQuery = facultyQuery.c_str();
    qstate = mysql_query(conn, fQuery);

    if (!qstate) {
        
        cout << "==============================================================================================================================================================" << endl;
        cout << "|                                                                          COURSE INFO                                                                       |" << endl;
        cout << "|------------------------------------------------------------------------------------------------------------------------------------------------------------|" << endl;
        cout << "| Course Code | Course Name                                                                      | Required CGPA    | Minimum CGPA | Minimum Work Experience |" << endl;
        cout << "|============================================================================================================================================================|" << endl;
        cout << "|             |                                                                                  |                  |              |                         |" << endl;
        res = mysql_store_result(conn);
        while (row = mysql_fetch_row(res)) {
            cout << left << "| " << setw(11) << row[2] << " | " << setw(81) << row[3] << "| " << setw(16) << row[4] << " | " << setw(12) << row[5] << " | " << setw(24) << row[6] << "| "  << endl;
            cout << "|             |                                                                                  |                  |              |                         |" << endl;
        }
        cout << "==============================================================================================================================================================" << endl << right << endl;
    }
    else {
        cout << "Query Execution Problem! MySQL Error #" << mysql_errno(conn) << endl;
    }
}
//End of Displaying list of Faculty and Courses (Student)


//Start of add grades/cgpa menu
void function::addGradesMenu() {
    cout << "( Welcome, user ";
    WriteInColor(11, username);//start here, the text color will be
    WriteInColor(7, " )\n"); // change back the next text colour to white
    cout << "=======================================================================================================" << endl;
    cout << "                                               STUDENT MENU                                            " << endl;
    cout << "                                               -add grades-                                            " << endl;
    cout << "=======================================================================================================" << endl;

    WriteInColor(11, "      +----------------------------------------------------------+\n"); //start here, the text color will be
    WriteInColor(11, "      | INSTRUCTION :                                            |\n");
    WriteInColor(11, "      | (1) Move arrow keys (Up, Down, Left, Right) to move the  |\n");
    WriteInColor(11, "      | selection and press ENTER key to select                  |\n");
    WriteInColor(11, "      | (2) Make sure the information you add is CORRECT!        |\n");
    WriteInColor(11, "      +----------------------------------------------------------+\n");

    WriteInColor(11, "      +-------------------+\n"); //start here, the text color will be blue
    WriteInColor(11, "      |    A  = 4.00      |\n");
    WriteInColor(11, "      |    A- = 3.67      |\n");
    WriteInColor(11, "      |    B+ = 3.33      |\n");
    WriteInColor(11, "      |    B  = 3.00      |\n");
    WriteInColor(11, "      |    B- = 2.67      |\n");
    WriteInColor(11, "      |    C+ = 2.33      |\n");
    WriteInColor(11, "      |    C  = 2.00      |\n");
    WriteInColor(11, "      |    C- = 1.67      |\n");
    WriteInColor(11, "      |    D  = 1.00      |\n");
    WriteInColor(11, "      |    F  = 0.00      |\n");
    WriteInColor(11, "      +-------------------+\n\n");
    WriteInColor(7, ""); // change back the next text colour to white
}
//Start of add grades/cgpa menu


//Start of add grades/cgpa function
void function::addGrades() {

    addGradesMenu();
    string gradeLetter;
    string subjectName;
    double gpa = 0;
    double cgpa = 0;
    int option;
    int totalSemester = 0;
    double a=0, b=0;

    do {//will loop if user didnt input number
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cout << "Enter total number of semester : ";
        cin >> totalSemester;
    } while (cin.fail());

    for (int i = 0; i < totalSemester; i++) { //i means current semester
        int currentSemester = i + 1;
        double creditHour;
        double gradePoints = 0;
        double totGradePoints = 0;
        double totCreditHour = 0;
        cout << "Calculate cgpa for semester " << currentSemester << endl;
        do {
        again:
            /*cout << "\nEnter the subject name : ";
            cin.ignore();
            getline(cin, subjectName);*/
            cout << "\nEnter grade (example : B+) : ";
            cin >> gradeLetter;
            cin.ignore();
            do {//will loop if user didnt input number
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                cout << "Enter the course credit hour: ";
                cin >> creditHour;
            } while (cin.fail());
   
            if (gradeLetter == "a" || gradeLetter == "A") {
                gradePoints = creditHour * 4.00;
            }
            else if (gradeLetter == "a-" || gradeLetter == "A-") {
                gradePoints = creditHour * 3.67;
            }
            else if (gradeLetter == "b+" || gradeLetter == "B+") {
                gradePoints = creditHour * 3.33;
            }
            else if (gradeLetter == "b" || gradeLetter == "B") {
                gradePoints = creditHour * 3.00;
            }
            else if (gradeLetter == "b-" || gradeLetter == "B-") {
                gradePoints = creditHour * 2.67;
            }
            else if (gradeLetter == "c+" || gradeLetter == "C+") {
                gradePoints = creditHour * 2.33;
            }
            else if (gradeLetter == "c" || gradeLetter == "C") {
                gradePoints = creditHour * 2.00;
            }
            else if (gradeLetter == "c-" || gradeLetter == "C-") {
                gradePoints = creditHour * 1.67;
            }
            else if (gradeLetter == "d" || gradeLetter == "D") {
                gradePoints = creditHour * 1.00;
            }
            else if (gradeLetter == "f" || gradeLetter == "F") {
                gradePoints = creditHour * 0.00;
            }
            else {
                cout << "Invaild Input..." << endl;
                goto again;
            }
            
            totGradePoints = totGradePoints + gradePoints;
            totCreditHour = totCreditHour + creditHour;

            cout << "Do you want to enter another grade (1 - Yes, 2 - no): ";
            cin >> option;
        } while (option == 1);

        //kira GPA
        gpa = totGradePoints / totCreditHour;
        //kira CGPA
        a = a + totGradePoints;
        b = b + totCreditHour;
        cgpa = a/b;


        //insert into database
        string cS = to_string(currentSemester); // change int to string
        string gpaDB = to_string(gpa); // change int to string
        string cgpaDB = to_string(cgpa); // change double to string
        string insertResultQuery = "insert into result (student_id, semester, gpa, cgpa) values ('"+ stuID + "', '" + cS + "', '" + gpaDB + "', '" + cgpaDB + "')";
        const char* insertResult = insertResultQuery.c_str();
        qstate = mysql_query(conn, insertResult);
        if (qstate)
        {
            cout << "10Query Execution Problem!" << mysql_errno(conn) << endl;
        }

        system("cls");
        addGradesMenu();
        cout << "Student's GPA for semester " << currentSemester << " is : " << setprecision(3) << gpa << "\n";
        cout << "Student's CGPA is : " << setprecision(3) << cgpa << "\n";
        system("pause");
        system("cls");
        addGradesMenu();
    }
}
//End of add grades/cgpa function


//Start of application menu
void function::applicationMenu() {
    WriteInColor(7, "( Welcome, user ");
    WriteInColor(11, username);//start here, the text color will be
    WriteInColor(7, " )\n"); // change back the next text colour to white
    cout << "=======================================================================================================" << endl;
    cout << "                                               STUDENT MENU                                            " << endl;
    cout << "                                           -course application-                                        " << endl;
    cout << "=======================================================================================================" << endl;

    WriteInColor(11, "                       +----------------------------------------------------------+\n"); //start here, the text color will be
    WriteInColor(11, "                       | INSTRUCTION :                                            |\n");
    WriteInColor(11, "                       | (1) Enter 0 during the selection to go back to faculty   |\n");
    WriteInColor(11, "                       | selection                                                |\n");
    WriteInColor(11, "                       | (2) You need to select 3 courses for the application     |\n");
    WriteInColor(11, "                       | (3) Make sure the information you add is CORRECT!        |\n");
    WriteInColor(11, "                       +----------------------------------------------------------+\n");
    WriteInColor(7, ""); // change back the next text colour to white
}
//Start of application menu


//Start of application function
void function::application() {

    arrowKeySelection arrow;
    int facultyselect = 0, check = 2; // check = 1 for display faculty n courses
    string course[3] = {"1","2","3"};

    for (int i = 0; i < 3; i++) {
        back:
        applicationMenu(); //display title
        cout << endl << endl;
        cout << setw(73) << "-Choose your desired courses for course " << i + 1 << "-";

        facultyselect = arrow.facultySelection(check); //arrow selection faculty, then cls
        string fs = to_string(facultyselect); // change int to string

        applicationMenu(); //display title
        cout << endl << endl;
        cout << setw(73) << "-Choose your desired courses for course " << i + 1 << "-\n\n";

        //to display courses based on faculty
        string facultyQuery = "select * from courses where faculty_id = '" + fs + "'";
        const char* fQuery = facultyQuery.c_str();
        qstate = mysql_query(conn, fQuery);
        if (!qstate) {
            res = mysql_store_result(conn);
            while (row = mysql_fetch_row(res)) {
                cout << "Course Code : " << row[2] << setw(20) << "Course Name : " << row[3] << endl;
            }
        }
        else {
            cout << "Query Execution Problem! MySQL Error #" << mysql_errno(conn) << endl;
        }

        cout << endl << endl;
        again:
        cout << setw(63) << "Enter course code for your desired course " << i + 1 << "  or enter 0 to go back : ";
        cin >> course[i];
        if (course[i] == "0") {
            system("cls");
            goto back;
        }

        //check if course is available in db
        string checkQuery = "select programme_code from courses where programme_code = '" + course[i] + "'";
        const char* cQ = checkQuery.c_str();
        qstate = mysql_query(conn, cQ);
        if (!qstate) {
            res = mysql_store_result(conn);
            if (res->row_count == 1){ //check if the course code is same in database
                if ( (course[2] == course[0]) || (course[2] == course[1]) || (course[1] == course[0]) ){ //check if student apply for the same course
                    cout << setw(85) << "YOU HAVE ALREADY INPUT THE COURSE, PLEASE CHOOSE OTHER COURSES" << endl << endl;
                    goto again;
                }
                else {
                    cout << endl << endl;
                    cout << setw(66) << "SUCCESSFULLY ADDED COURSE " << i + 1 << endl;
                }        
            }
            else {
                goto again;
            }
        }
        else {
            cout << "Query Execution Problem! MySQL Error #" << mysql_errno(conn) << endl;
        }
        system("pause");
        system("cls");
    }

    //SQL ADD ALL 3 COURSES INTO TABLE
    string addApplicationQuery = "insert into application (student_id, course1, course2, course3) values ('" + stuID + "', '" + course[0] + "', '" + course[1] + "', '" + course[2] + "')";
    const char* addApplication = addApplicationQuery.c_str();
    qstate = mysql_query(conn, addApplication);
    if (!qstate) {

        //SQL INCREMENT NUMBER OF STUDENTS APPLY FOR SPECIFIC COURSES
        for (int i = 0; i < 3; i++) {
            string incrementStudent = "UPDATE courses SET numOfStudent = IFNULL(numOfStudent, 0) + 1 WHERE programme_code = '" + course[i] + "'";
            const char* iSQuery = incrementStudent.c_str();
            qstate = mysql_query(conn, iSQuery);
            if (qstate) {
                cout << "Query Execution Problem! query " << i+1 <<"MySQL Error #" << mysql_errno(conn) << endl;
            }
        }
        //END OF SQL INCREMENT NUMBER OF STUDENTS APPLY FOR SPECIFIC COURSES
        string makeApplication = "UPDATE studentdetails SET make_application = 1 WHERE student_id = '" + stuID + "'";
        const char* maQuery = makeApplication.c_str();
        qstate = mysql_query(conn, maQuery);
        if (!qstate) {
            applicationMenu(); //display title
            cout << endl << endl;
            cout << setw(73) << "YOU HAVE SUCCESSFULLY REGISTERED YOUR COURSES" << endl;
        }
    }
    else {
        cout << "Query Execution Problem! MySQL Error #" << mysql_errno(conn) << endl;
    }
    check = 0; //reset check
}
//End of application function


//Start of view application function
void function::viewApplication() {
    cout << "( Welcome, user ";
    WriteInColor(11, username);//start here, the text color will be
    WriteInColor(7, " )\n"); // change back the next text colour to white
    cout << "=======================================================================================================" << endl;
    cout << "                                               STUDENT MENU                                            " << endl;
    cout << "                                            -view application-                                         " << endl;
    cout << "=======================================================================================================" << endl << endl;

    cout << "==================================================================================================" << endl;
    cout << "|                                        APPLICATION INFO                                        |" << endl;
    cout << "|------------------------------------------------------------------------------------------------|" << endl;
    cout << "| Course Code | Course Name                                                                      |" << endl;
    cout << "|================================================================================================|" << endl;

    //display course 1
    string facultyQuery1 = "select programme_code, programme_name from courses where programme_code in(select course1 from application where student_id = '" + stuID + "')";
    const char* fQuery1 = facultyQuery1.c_str();
    qstate = mysql_query(conn, fQuery1);
    if (!qstate) {
        res = mysql_store_result(conn);
        while (row = mysql_fetch_row(res)) {
            cout << left << "| " << setw(11) << row[0] << " | " << setw(81) << row[1] << "| "  << endl;
            cout << "|------------------------------------------------------------------------------------------------|" << endl;
        }
    }
    //display course 2
    string facultyQuery2 = "select programme_code, programme_name from courses where programme_code in(select course2 from application where student_id = '" + stuID + "')";
    const char* fQuery2 = facultyQuery2.c_str();
    qstate = mysql_query(conn, fQuery2);
    if (!qstate) {
        res = mysql_store_result(conn);
        while (row = mysql_fetch_row(res)) {
            cout << left << "| " << setw(11) << row[0] << " | " << setw(81) << row[1] << "| " << endl;
            cout << "|------------------------------------------------------------------------------------------------|" << endl;
        }
    }
    //display course 3
    string facultyQuery3 = "select programme_code, programme_name from courses where programme_code in(select course3 from application where student_id = '" + stuID + "')";
    const char* fQuery3 = facultyQuery3.c_str();
    qstate = mysql_query(conn, fQuery3);
    if (!qstate) {
        res = mysql_store_result(conn);
        while (row = mysql_fetch_row(res)) {
            cout << left << "| " << setw(11) << row[0] << " | " << setw(81) << row[1] << "| " << endl;
            cout << "|================================================================================================|" << endl << right;
        }
    }
}
//End of view application function


//Start of application result function
void function::applicationResult() {
    cout << "( Welcome, user ";
    WriteInColor(11, username);//start here, the text color will be
    WriteInColor(7, " )\n"); // change back the next text colour to white
    cout << "=======================================================================================================" << endl;
    cout << "                                               STUDENT MENU                                            " << endl;
    cout << "                                           -application result-                                        " << endl;
    cout << "=======================================================================================================" << endl << endl;

    string result, makeApplication;

    string getResult = "select student_id,IFNULL(application_result, 0), make_application from studentdetails where student_id = '" + stuID + "'";
    const char* grQuery = getResult.c_str();
    qstate = mysql_query(conn, grQuery);
    if (!qstate) {
        res = mysql_store_result(conn);
        if (res->row_count == 1) { //
            while (row = mysql_fetch_row(res)) {
                result = row[1];
                makeApplication = row[2];
            }
        }
        if ((result == "0") && (makeApplication == "2")) {  // IF "NULL"/0 MEANS THAT THE STUDENT DID NOT MANAGE TO GET COURSES THEY WANTED
            cout << setw(73) << "We are sorry to inform you that your application are "; WriteInColor(12, "NOT SUCCESSFUL"); WriteInColor(7, "."); cout << endl;
        }
        else if (makeApplication == "1") {
            cout << setw(73); WriteInColor(10, "Please wait until the admin approve your course. :) Thankyou for understanding!"); WriteInColor(7, ".");  cout << endl;
        }
        else { //
            string displayResult = "select programme_code, programme_name from courses where programme_code in(select application_result from studentdetails where student_id = '" + stuID + "')";
            const char* drQuery = displayResult.c_str();
            qstate = mysql_query(conn, drQuery);
            if (!qstate) {
                res = mysql_store_result(conn);
                while (row = mysql_fetch_row(res)) {
                    cout << setw(73) << "We are happy to inform you that your application is "; WriteInColor(10, "SUCCESSFUL"); WriteInColor(7, "."); cout << endl << endl;
                    cout << "Course Code : " << row[0] << endl;
                    cout << "Course Name : " << row[1] << endl;                    
                }
            }
        }
    }
    else {
        cout << "Query Execution Problem! MySQL Error #" << mysql_errno(conn) << endl;
    }


}
//End of application result function


//Start of admin login function 
int function::adminLogin() {

    int count = 0;
    admin_login:
    string adminName, adminPass = "", adminPasswordDB;
    char ch;

    cout << "========================================================================" << endl;
    cout << "                               ADMIN LOGIN                              " << endl;
    cout << "========================================================================" << endl;
    cout << "Enter Admin Username : ";
    //cin.ignore();
    getline(cin >> ws, adminName);

    cout << "Enter Admin Password : ";
    while (ch = _getch()) { //assign ASCII value to ch
        if (ch == 13) {  //13 is ENTER key in ASCII

            string adminLoginQuerry = "select * from admin where admin_username = '" + adminName + "' and admin_password = '" + adminPass + "'";
            const char* adminLogin = adminLoginQuerry.c_str();
            qstate = mysql_query(conn, adminLogin);

            if (!qstate) {
                res = mysql_store_result(conn);
                if (res->row_count == 1) { //
                    while (row = mysql_fetch_row(res)) {
                        adminID = row[0]; //ibarat $_SESSION dalam php la gitu (row[0] is row admin id dalam database)
                        adminUser = row[1];
                        adminPasswordDB = row[2]; //row[5] for password
                    }
                }
                if ((adminPass == adminPasswordDB) && (adminName == adminUser)) {//password exaclty sama ngan database
                    system("cls");
                    cout << "========================================================================" << endl;
                    cout << "                               ADMIN LOGIN                              " << endl;
                    cout << "========================================================================" << endl;
                    cout << "\nCORRECT LOGIN!" << endl;
                    //cout << endl << ifstream("interface/CorrectLogin.txt").rdbuf() << endl << endl << endl << endl;
                    system("pause");
                    system("cls");
                    return count = 0;
                }
                else if ((adminPass != adminPasswordDB) && (adminName != adminUser)) {
                    adminName = "";
                    adminPass = "";
                    count++;
                    if (count == 3) { //if student unable to login 3 times, the program will go back to main()
                        system("cls");
                        Beep(1000, 500);
                        cout << "========================================================================" << endl;
                        cout << "                               ADMIN LOGIN                              " << endl;
                        cout << "========================================================================" << endl;
                        cout << "\nERROR, INCORRECT ADMIN USERNAME or PASSWORD\nYOU WILL GO BACK TO MAIN MENU" << endl;
                        //cout << endl << ifstream("interface/ErrorLogin.txt").rdbuf() << endl << endl << endl << endl;
                        system("pause");
                        system("cls");
                        return count;
                    }
                    else { //if student unable to login, the program will go back to login page again()
                        system("cls");
                        Beep(1000, 500);
                        cout << "========================================================================" << endl;
                        cout << "                               ADMIN LOGIN                              " << endl;
                        cout << "========================================================================" << endl;
                        cout << "\nERROR, INCORRECT ADMIN USERNAME or PASSWORD" << endl;
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
            if (adminPass.length() > 0) { //set condition blocking error while input
                cout << "\b \b"; //delete * everytime user click backspace
                adminPass.erase(adminPass.length() - 1); //erase string length
            }
        }
        else {
            //make password cannot be seen, when input it display as pasword : ************
            cout << "*";
            adminPass += ch;
        }
    }
}
//End of admin login function 


//start of admin menu function
void function::adminMenu() {
    WriteInColor(7, "( Welcome, user ");
    WriteInColor(11, adminUser + " " + adminID);//start here, the text color will be
    WriteInColor(7, " )\n"); // change back the next text colour to white
    cout << "=======================================================================================================" << endl;
    cout << "                                                ADMIN MENU                                             " << endl;
    cout << "=======================================================================================================" << endl;

    WriteInColor(11, "                       +----------------------------------------------------------+\n"); //start here, the text color will be
    WriteInColor(11, "                       | INSTRUCTION :                                            |\n");
    WriteInColor(11, "                       | Move arrow keys (Up, Down, Left, Right) to move the      |\n");
    WriteInColor(11, "                       | selection and press ENTER key to select                  |\n");
    WriteInColor(11, "                       +----------------------------------------------------------+\n");
    WriteInColor(7, ""); // change back the next text colour to white
}


//Start of admin view graph menu
void function::adminViewGraphMenu() {
    WriteInColor(7, "( Welcome, user ");
    WriteInColor(11, adminUser + " " + adminID);//start here, the text color will be
    WriteInColor(7, " )\n"); // change back the next text colour to white
    cout << "=======================================================================================================" << endl;
    cout << "                                                ADMIN MENU                                             " << endl;
    cout << "                                               -view graph-                                            " << endl;
    cout << "=======================================================================================================" << endl << endl;

    WriteInColor(11, "                       +----------------------------------------------------------+\n"); //start here, the text color will be
    WriteInColor(11, "                       | INSTRUCTION :                                            |\n");
    WriteInColor(11, "                       | Move arrow keys (Up, Down, Left, Right) to move the      |\n");
    WriteInColor(11, "                       | selection and press ENTER key to select                  |\n");
    WriteInColor(11, "                       +----------------------------------------------------------+\n");
    WriteInColor(7, ""); // change back the next text colour to white
}
//End of admin view graph menu


//start of admin view graph function
void function::adminViewGraph() {

    adminViewGraphMenu();
    int graphSelect = 0;

    arrowKeySelection arrow;
    graphSelect = arrow.adminGraphSelection();

    if (graphSelect == 1) { //View Total Registered Users
        adminViewGraphMenu();
        string numOfRegisteredStudent,numOfStudentApplication;

        //START OF GET NUMBER OF REGISTERED USER
        string countRegisteredStudent = "SELECT COUNT(*) FROM STUDENT";
        const char* cruQuery = countRegisteredStudent.c_str();
        qstate = mysql_query(conn, cruQuery);
        if (!qstate) {
            res = mysql_store_result(conn);
            if (res->row_count == 1) { //
                while (row = mysql_fetch_row(res)) {
                    numOfRegisteredStudent = row[0];
                }
            }
        }
        else {
            cout << "Query Execution Problem! MySQL Error #" << mysql_errno(conn) << endl;
        }
        //END OF GET NUMBER OF REGISTERED USER

        //START OF GET NUMBER OF STUDENT WHO ALREADY APPLIED
        string countStudentApplication = "SELECT COUNT(*) FROM application";
        const char* csaQuery = countStudentApplication.c_str();
        qstate = mysql_query(conn, csaQuery);
        if (!qstate) {
            res = mysql_store_result(conn);
            if (res->row_count == 1) { //
                while (row = mysql_fetch_row(res)) {
                    numOfStudentApplication = row[0];
                }
            }
        }
        else {
            cout << "Query Execution Problem! MySQL Error #" << mysql_errno(conn) << endl;
        }
        //END OF GET NUMBER OF STUDENT WHO ALREADY APPLIED


        //CASTING, CHANGE STRING TO INT
        stringstream registered(numOfRegisteredStudent); //Number of registered student
        int x = 0;
        registered >> x; 

        stringstream stuApp(numOfStudentApplication); //Number of student who already apply for courses
        int y = 0;
        stuApp >> y; 
        // END OF CASTING, CHANGE STRING TO INT

        cout << setw(62) << " +--------------+ " << endl;
        cout << setw(62) << " |  Bar graphs  | " << endl;
        cout << setw(62) << " +--------------+ " << endl << endl ;

        cout << right << setw(46) << "|" << endl;
        cout << setw(47) << right << "Registered Students | " << setw(1) << left; //cout << setw(31) << right << " |" << endl;
        WriteInColor(11, "");
        if (x == 0) {
            WriteInColor(7, "  ");
            cout << endl;
        }
        else {
            for (int j = 1; j <= x; j++) { // j <= Number of student who already apply for courses
                cout << char(219); //display bar
                if (j == x) {
                    WriteInColor(7, "  ");
                    cout << j << endl;
                }
            }
        }

        cout << right << setw(46) << "|" << endl;
        cout << setw(47) << right << "Student who have applied 3 courses | " << setw(1) << left;
        WriteInColor(11, "");
        if (y == 0) {
            WriteInColor(7, "  ");
            cout << endl;
        }
        else {
            for (int j = 1; j <= y; j++) { // j <= Number of student who already apply for courses
                cout << char(219); //display bar
                if (j == y) {
                    WriteInColor(7, "  ");
                    cout << j << endl;
                }
            }
        }
        cout << right << setw(118) << "|------------------------------------------------------> num. of students" << endl;

    }
    else if (graphSelect == 2) { //View Total Number of Students In Each Faculty
        adminViewGraphMenu();
        string facultyAviation, facultyCS, facultyChemical, facultyBusiness,facultyHealth;
        string approvedAviation, approvedCS, approvedChemical, approvedBusiness, approvedHealth;

        //START OF GET NUMBER OF STUDENTS IN AVIATION
        string countStudentFaculty1 = "SELECT IFNULL(SUM(numOfStudent), 0),IFNULL(SUM(approvedStudent), 0) FROM courses where faculty_id = 1";
        const char* csfQuery1 = countStudentFaculty1.c_str();
        qstate = mysql_query(conn, csfQuery1);
        if (!qstate) {
            res = mysql_store_result(conn);
            if (res->row_count == 1) { //
                while (row = mysql_fetch_row(res)) {
                    facultyAviation = row[0];
                    approvedAviation = row[1];
                }
            }
        }
        //END OF GET NUMBER OF STUDENTS IN AVIATION

        //START OF GET NUMBER OF STUDENTS IN COMP SCIENCE
        string countStudentFaculty2 = "SELECT IFNULL(SUM(numOfStudent), 0),IFNULL(SUM(approvedStudent), 0) FROM courses where faculty_id = 2";
        const char* csfQuery2 = countStudentFaculty2.c_str();
        qstate = mysql_query(conn, csfQuery2);
        if (!qstate) {
            res = mysql_store_result(conn);
            if (res->row_count == 1) { //
                while (row = mysql_fetch_row(res)) {
                    facultyCS = row[0];
                    approvedCS = row[1];
                }
            }
        }
        //END OF GET NUMBER OF STUDENTS IN COMP SCIENCE

        //START OF GET NUMBER OF STUDENTS IN CHEMICAL ENGINEERING
        string countStudentFaculty3 = "SELECT IFNULL(SUM(numOfStudent), 0),IFNULL(SUM(approvedStudent), 0) FROM courses where faculty_id = 3";
        const char* csfQuery3 = countStudentFaculty3.c_str();
        qstate = mysql_query(conn, csfQuery3);
        if (!qstate) {
            res = mysql_store_result(conn);
            if (res->row_count == 1) { //
                while (row = mysql_fetch_row(res)) {
                    facultyChemical = row[0];
                    approvedChemical = row[1];
                }
            }
        }
        //END OF GET NUMBER OF STUDENTS IN CHEMICAL ENGINEERING

        //START OF GET NUMBER OF STUDENTS IN BUSINESS/ACCOUNT
        string countStudentFaculty4 = "SELECT IFNULL(SUM(numOfStudent), 0),IFNULL(SUM(approvedStudent), 0) FROM courses where faculty_id = 4";
        const char* csfQuery4 = countStudentFaculty4.c_str();
        qstate = mysql_query(conn, csfQuery4);
        if (!qstate) {
            res = mysql_store_result(conn);
            if (res->row_count == 1) { //
                while (row = mysql_fetch_row(res)) {
                    facultyBusiness = row[0];
                    approvedBusiness = row[1];
                }
            }
        }
        //END OF GET NUMBER OF STUDENTS IN BUSINESS/ACCOUNT

        //START OF GET NUMBER OF STUDENTS IN HEALTH SCIENCES
        string countStudentFaculty5 = "SELECT IFNULL(SUM(numOfStudent), 0),IFNULL(SUM(approvedStudent), 0) FROM courses where faculty_id = 5";
        const char* csfQuery5 = countStudentFaculty5.c_str();
        qstate = mysql_query(conn, csfQuery5);
        if (!qstate) {
            res = mysql_store_result(conn);
            if (res->row_count == 1) { //
                while (row = mysql_fetch_row(res)) {
                    facultyHealth = row[0];
                    approvedHealth = row[1];
                }
            }
        }
        //END OF GET NUMBER OF STUDENTS IN HEALTH SCIENCES


        //CASTING, CHANGE STRING TO INT
        stringstream avi(facultyAviation); //Number of registered student
        int a = 0;
        avi >> a;
        stringstream cs(facultyCS); //Number of student who already apply for courses
        int b = 0;
        cs >> b;
        stringstream ch(facultyChemical); //Number of student who already apply for courses
        int c = 0;
        ch >> c;
        stringstream bs(facultyBusiness); //Number of student who already apply for courses
        int d = 0;
        bs >> d;
        stringstream h(facultyHealth); //Number of student who already apply for courses
        int e = 0;
        h >> e;
        // END OF CASTING, CHANGE STRING TO INT
        cout << endl << endl << endl;
        cout << setw(92) << " +-----------------------------------------------------------+ " << endl;
        cout << setw(92) << " |  Graph : Total number of students apply for each faculty  | " << endl;
        cout << setw(92) << " +-----------------------------------------------------------+ " << endl << endl;

        cout << right << setw(46) << "|" << endl;
        cout << setw(47) << right << "Faculty of Aviation | " << setw(1) << left; //cout << setw(31) << right << " |" << endl;
        WriteInColor(11, "");
        if (a == 0) {
            WriteInColor(7, "  ");
            cout << endl;
        }
        else {
            for (int j = 1; j <= a; j++) { // j <= Number of student who already apply for courses
                cout << char(219); //display bar
                if (j == a) {
                    WriteInColor(7, "  ");
                    cout << j << endl;
                }
            }
        }

        cout << right << setw(46) << "|" << endl;
        cout << setw(47) << right << "Faculty of Computer Science & Mathematics | " << setw(1) << left;
        WriteInColor(11, "");
        if (b == 0) {
            WriteInColor(7, "  ");
            cout << endl;
        }
        else {
            for (int j = 1; j <= b; j++) { // j <= Number of student who already apply for courses
                cout << char(219); //display bar
                if (j == b) {
                    WriteInColor(7, "  ");
                    cout << j << endl;
                }
            }
        }

        cout << right << setw(46) << "|" << endl;
        cout << setw(47) << right << "Faculty of Chemical Engineering | " << setw(1) << left;
        WriteInColor(11, "");
        if (c == 0) {
            WriteInColor(7, "  ");
            cout << endl;
        }
        else {
            for (int j = 1; j <= c; j++) { // j <= Number of student who already apply for courses
                cout << char(219); //display bar
                if (j == c) {
                    WriteInColor(7, "  ");
                    cout << j << endl;
                }
            }
        }

        cout << right << setw(46) << "|" << endl;
        cout << setw(47) << right << "Faculty of Business and Accountancy | " << setw(1) << left;
        WriteInColor(11, "");
        if (d == 0) {
            WriteInColor(7, "  ");
            cout << endl;
        }
        else {
            for (int j = 1; j <= d; j++) { // j <= Number of student who already apply for courses
                cout << char(219); //display bar
                if (j == d) {
                    WriteInColor(7, "  ");
                    cout << j << endl;
                }
            }
        }

        cout << right << setw(46) << "|" << endl;
        cout << setw(47) << right << "Faculty of Health Sciences | " << setw(1) << left;
        WriteInColor(11, "");
        if (e == 0) {
            WriteInColor(7, "  ");
            cout << endl;
        }
        else {
            for (int j = 1; j <= e; j++) { // j <= Number of student who already apply for courses
                cout << char(219); //display bar
                if (j == e) {
                    WriteInColor(7, "  ");
                    cout << j << endl;
                }
            }
        }
        cout << right << setw(118) << "|------------------------------------------------------> num. of students" << endl << endl << endl;

        //CASTING, CHANGE STRING TO INT
        stringstream avi2(approvedAviation); //Number of registered student
        int a2 = 0;
        avi2 >> a2;
        stringstream cs2(approvedCS); //Number of student who already apply for courses
        int b2 = 0;
        cs2 >> b2;
        stringstream ch2(approvedChemical); //Number of student who already apply for courses
        int c2 = 0;
        ch2 >> c2;
        stringstream bs2(approvedBusiness); //Number of student who already apply for courses
        int d2 = 0;
        bs2 >> d2;
        stringstream h2(approvedHealth); //Number of student who already apply for courses
        int e2 = 0;
        h2 >> e2;
        // END OF CASTING, CHANGE STRING TO INT

        cout << setw(92) << " +-------------------------------------------------------------+ " << endl;
        cout << setw(92) << " |  Graph : Total number of students approved in each faculty  | " << endl;
        cout << setw(92) << " +-------------------------------------------------------------+ " << endl << endl;

        cout << right << setw(46) << "|" << endl;
        cout << setw(47) << right << "Faculty of Aviation | " << setw(1) << left; //cout << setw(31) << right << " |" << endl;
        WriteInColor(11, "");
        if (a2 == 0) {
            WriteInColor(7, "  ");
            cout << endl;
        }
        else {
            for (int j = 1; j <= a2; j++) { // j <= Number of student who already apply for courses
                cout << char(219); //display bar
                if (j == a2) {
                    WriteInColor(7, "  ");
                    cout << j << endl;
                }
            }
        }

        cout << right << setw(46) << "|" << endl;
        cout << setw(47) << right << "Faculty of Computer Science & Mathematics | " << setw(1) << left;
        WriteInColor(11, "");
        if (b2 == 0) {
            WriteInColor(7, "  ");
            cout << endl;
        }
        else {
            for (int j = 1; j <= b2; j++) { // j <= Number of student who already apply for courses
                cout << char(219); //display bar
                if (j == b2) {
                    WriteInColor(7, "  ");
                    cout << j << endl;
                }
            }
        }

        cout << right << setw(46) << "|" << endl;
        cout << setw(47) << right << "Faculty of Chemical Engineering | " << setw(1) << left;
        WriteInColor(11, "");
        if (c2 == 0) {
            WriteInColor(7, "  ");
            cout << endl;
        }
        else {
            for (int j = 1; j <= c2; j++) { // j <= Number of student who already apply for courses
                cout << char(219); //display bar
                if (j == c2) {
                    WriteInColor(7, "  ");
                    cout << j << endl;
                }
            }
        }

        cout << right << setw(46) << "|" << endl;
        cout << setw(47) << right << "Faculty of Business and Accountancy | " << setw(1) << left;
        WriteInColor(11, "");
        if (d2 == 0) {
            WriteInColor(7, "  ");
            cout << endl;
        }
        else {
            for (int j = 1; j <= d2; j++) { // j <= Number of student who already apply for courses
                cout << char(219); //display bar
                if (j == d2) {
                    WriteInColor(7, "  ");
                    cout << j << endl;
                }
            }
        }

        cout << right << setw(46) << "|" << endl;
        cout << setw(47) << right << "Faculty of Health Sciences | " << setw(1) << left;
        WriteInColor(11, "");
        if (e2 == 0) {
            WriteInColor(7, "  ");
            cout << endl;
        }
        else {
            for (int j = 1; j <= e2; j++) { // j <= Number of student who already apply for courses
                cout << char(219); //display bar
                if (j == e2) {
                    WriteInColor(7, "  ");
                    cout << j << endl;
                }
            }
        }
        
        cout << right << setw(127) << "|------------------------------------------------------> num. of approved students" << endl;
    }
    else if (graphSelect == 3) {
        adminStudentListMenu();
    }

}
//end of admin view graph function


//Start of admin view graph menu
void function::adminStudentListMenu() {
    WriteInColor(7, "( Welcome, user ");
    WriteInColor(11, adminUser + " " + adminID);//start here, the text color will be
    WriteInColor(7, " )\n"); // change back the next text colour to white
    cout << "=======================================================================================================" << endl;
    cout << "                                                ADMIN MENU                                             " << endl;
    cout << "                                          -view list of student-                                       " << endl;
    cout << "=======================================================================================================" << endl << endl;

    WriteInColor(11, "                       +----------------------------------------------------------+\n"); //start here, the text color will be
    WriteInColor(11, "                       | INSTRUCTION :                                            |\n");
    WriteInColor(11, "                       | Move arrow keys (Up, Down, Left, Right) to move the      |\n");
    WriteInColor(11, "                       | selection and press ENTER key to select                  |\n");
    WriteInColor(11, "                       +----------------------------------------------------------+\n");
    WriteInColor(7, "\n\n"); // change back the next text colour to white
}
//End of admin view graph menu


//start of admin view list of student function
void function::adminViewStudentList() {

    adminStudentListMenu();
    int listSelect = 0, check = 2;

    arrowKeySelection arrow;
    listSelect = arrow.adminStudentListSelection();

    if (listSelect == 1) { //List Of Registered Students
        adminStudentListMenu();
        // SELECT * FROM result WHERE student_id = 1 AND semester = (SELECT MAX(semester) FROM result)               --> get cgpa
        string displayRegisteredStudent = "SELECT student.*, studentdetails.* FROM student JOIN studentdetails on student.student_id = studentdetails.student_id";
        const char* dsaQuery = displayRegisteredStudent.c_str();
        qstate = mysql_query(conn, dsaQuery);
        if (!qstate) {
            res = mysql_store_result(conn);
            cout << setw(82) << "LIST OF REGISTERED STUDENT WHO HAVE INSERTED STUDENT DETAILS" << endl;
            cout << setw(106) << "==================================================================================================" << endl;
            cout << setw(106) << "| Student ID |           Username           |     IC_Number     |   Gender   |  Education Level  |" << endl;
            cout << setw(106) << "==================================================================================================" << endl;
            cout << setw(106) << "|            |                              |                   |            |                   |" << endl;
            while (row = mysql_fetch_row(res)) {
                cout << setw(9) << "|" << setw(11) << row[0] << " |" << setw(29) << row[1] << " |" << setw(18) << row[2] << " |" << setw(11) << row[3] << " |" << setw(18) << row[12] << " |" << endl;
            }
            cout << setw(106) << "==================================================================================================" << endl << endl << endl;
        }
        else {
            cout << "Query Execution Problem! MySQL Error #" << mysql_errno(conn) << endl;
        }
        
    }else if (listSelect == 2) { //List Of Student Based On EDUCATION LEVEL
        adminStudentListMenu();
        string edu;
        cout << setw(62) << "Choose education level" << endl;
        int eduSelect = arrow.eduLevelSelection(check);
        if (eduSelect == 1)
            edu = "Diploma";
        else if (eduSelect == 2)
            edu = "STPM";
        else if (eduSelect == 3)
            edu = "Matriculation";
        else if (eduSelect == 4)
            edu = "Foundation";
        else if (eduSelect == 5)
            edu = " A-Level";

        system("cls");
        adminStudentListMenu();

        string displayRegisteredStudent = "SELECT student.*, studentdetails.* FROM student JOIN studentdetails on student.student_id = studentdetails.student_id"
                                          " WHERE education_level = '" + edu + "'";
        const char* dsaQuery = displayRegisteredStudent.c_str();
        qstate = mysql_query(conn, dsaQuery);
        if (!qstate) {
            res = mysql_store_result(conn);
            cout << setw(76) << "LIST OF STUDENT BASED ON EDUCATION LEVEL" << endl;
            cout << setw(106) << "==================================================================================================" << endl;
            cout << setw(106) << "| Student ID |           Username           |     IC_Number     |   Gender   |  Education Level  |" << endl;
            cout << setw(106) << "==================================================================================================" << endl;
            cout << setw(106) << "|            |                              |                   |            |                   |" << endl;
            while (row = mysql_fetch_row(res)) {
                cout << setw(9) << "|" << setw(11) << row[0] << " |" << setw(29) << row[1] << " |" << setw(18) << row[2] << " |" << setw(11) << row[3] << " |" << setw(18) << row[12] << " |" << endl;
            }
            cout << setw(106) << "==================================================================================================" << endl << endl << endl;
        }
        else {
            cout << "Query Execution Problem! MySQL Error #" << mysql_errno(conn) << endl;
        }
    }
    else if (listSelect == 3) { //View List Of Approved Student Based on COURSES
        adminStudentListMenu();
        string courseCode, courseName;
        check = 1;
        int fselect = arrow.facultySelection(check);
        string fs = to_string(fselect); // change int to string

        system("cls");
        adminStudentListMenu();
        string facultyQuery = "select * from courses where faculty_id = '" + fs + "'";
        const char* fQuery = facultyQuery.c_str();
        qstate = mysql_query(conn, fQuery);
        if (!qstate) {
            res = mysql_store_result(conn);
            while (row = mysql_fetch_row(res)) {
                cout << "Course Code : " << row[2] << setw(20) << "Course Name : " << row[3] << endl;
            }
        }
        else {
            cout << "Query Execution Problem! MySQL Error #" << mysql_errno(conn) << endl;
        }

        cout << endl << endl;
        cout << setw(62) << "SELECT COURSE CODE TO VIEW TABLE ==> ";
        cin >> courseCode;

        system("cls");
        adminStudentListMenu();

        string getCourseName = "select programme_name from courses where programme_code = '" + courseCode + "'";
        const char* gcnQuery = getCourseName.c_str();
        qstate = mysql_query(conn, gcnQuery);
        if (!qstate) {
            res = mysql_store_result(conn);
            while (row = mysql_fetch_row(res)) {
                courseName = row[0];
            }
        }
        else {
            cout << "Query Execution Problem! MySQL Error #" << mysql_errno(conn) << endl;
        }

        string displayRegisteredStudent = "SELECT student.*, studentdetails.* FROM student JOIN studentdetails on student.student_id = studentdetails.student_id"
            " WHERE application_result = '" + courseCode + "'";
        const char* dsaQuery = displayRegisteredStudent.c_str();
        qstate = mysql_query(conn, dsaQuery);
        if (!qstate) {
            res = mysql_store_result(conn);
            cout  << courseName << endl;
            cout  << "==================================================================================================" << endl;
            cout  << "| Student ID |           Username           |     IC_Number     |   Gender   |  Education Level  |" << endl;
            cout  << "==================================================================================================" << endl;
            cout << setw(106) << "|            |                              |                   |            |                   |" << endl;
            while (row = mysql_fetch_row(res)) {
                cout  << "|" << setw(11) << row[0] << " |" << setw(29) << row[1] << " |" << setw(18) << row[2] << " |" << setw(11) << row[3] << " |" << setw(18) << row[12] << " |" << endl;
            }
            cout  << "==================================================================================================" << endl << endl << endl;
            
        }
        else {
            cout << "Query Execution Problem! MySQL Error #" << mysql_errno(conn) << endl;
        }

    }
    else if (listSelect == 4) { //Back to Admin Main Menu
        adminStudentListMenu();
    }
}
//end of admin view list of student function


//start of application approval function
void function::adminApproval() {
    applicationAdminAgain:
    WriteInColor(7, "( Welcome, user ");
    WriteInColor(11, adminUser + " " + adminID);//start here, the text color will be
    WriteInColor(7, " )\n"); // change back the next text colour to white
    cout << "=======================================================================================================" << endl;
    cout << "                                                ADMIN MENU                                             " << endl;
    cout << "                                          -application approval-                                       " << endl;
    cout << "=======================================================================================================" << endl << endl;

    WriteInColor(11, "                       +----------------------------------------------------------+\n"); //start here, the text color will be
    WriteInColor(11, "                       | INSTRUCTION :                                            |\n");
    WriteInColor(11, "                       | Move arrow keys (Up, Down, Left, Right) to move the      |\n");
    WriteInColor(11, "                       | selection and press ENTER key to select                  |\n");
    WriteInColor(11, "                       +----------------------------------------------------------+\n");
    WriteInColor(7, "\n\n"); // change back the next text colour to white

    string studentID;
    // SELECT * FROM result WHERE student_id = 1 AND semester = (SELECT MAX(semester) FROM result)               --> get cgpa
    string displayStudentApplication = "SELECT student.*, studentdetails.* FROM student JOIN studentdetails on student.student_id = studentdetails.student_id WHERE " 
                                       "studentdetails.make_application = 1"; //make_application = 1 = have data in application table
    const char* dsaQuery = displayStudentApplication.c_str();
    qstate = mysql_query(conn, dsaQuery);
    if (!qstate) {
        res = mysql_store_result(conn);
        cout << setw(82) << "LIST OF STUDENTS WAITING FOR COURSE APPLICATION APPROVAL" << endl;
        cout << setw(86) << "=================================================================" << endl;
        cout << setw(86) << "| Student ID |           Username           |     IC_Number     |" << endl;
        cout << setw(86) << "=================================================================" << endl;
        while (row = mysql_fetch_row(res)) {
            cout << setw(22) << "|" << setw(11) << row[0] << " |" << setw(29) << row[1] << " |" << setw(18) << row[2] << " |" << endl;
        }
        cout << setw(86) << "=================================================================" << endl << endl << endl;
    }
    else {
        cout << "Query Execution Problem! MySQL Error #" << mysql_errno(conn) << endl;
    }

    cout << setw(62) << "SELECT STUDENT ID ==> ";
    cin >> studentID;
    cout << "\n\n";
    string check;
    // ADD SQL CHECK IF STUDENT ID TAKDE, DIA TANYA AGAIN
    string checkQ = "SELECT EXISTS(select studentdetails.student_id from studentdetails"
                    "where studentdetails.make_application = 1 and studentdetails.student_id= '" + studentID + "')";
    const char* checkQuery = checkQ.c_str();
    qstate = mysql_query(conn, checkQuery);
    if (!qstate) {
        res = mysql_store_result(conn);
        if (res->row_count == 1) {
            while (row = mysql_fetch_row(res)) {
                check = row[0];
            }
        }
        if (check == "0") {
            cout << setw(59) << "Wrong Student ID" << endl << endl;
            system("pause");
            system("cls");
            goto applicationAdminAgain;
        }
    }
    else {
        cout << "Query Execution Problem! MySQL Error #" << mysql_errno(conn) << endl;
    }

    string countStudentFaculty1 = "SELECT student.*, studentdetails.*, result.* "
        "FROM student JOIN studentdetails on student.student_id = studentdetails.student_id "
        "JOIN result on result.student_id = student.student_id "
        "WHERE student.student_id = '" + studentID + "' "
        "AND result.semester = (SELECT MAX(semester) FROM result WHERE result.student_id= '" + studentID + "')";
    const char* csfQuery1 = countStudentFaculty1.c_str();
    qstate = mysql_query(conn, csfQuery1);
    if (!qstate) {

        string student_username, student_fullname, ic_num, work_exp, cgpa;
        string recommendedCGPA, minimumCGPA, minimumWork_exp;
        string course1 = "", course2 = "", course3 = "", approvedCourse;
        double doubleCGPA = 0;
        int intWork_exp = 0, count=0;

        system("cls");
        WriteInColor(7, "( Welcome, user ");
        WriteInColor(11, adminUser + " " + adminID);//start here, the text color will be
        WriteInColor(7, " )\n"); // change back the next text colour to white
        cout << "=======================================================================================================" << endl;
        cout << "                                                ADMIN MENU                                             " << endl;
        cout << "                                          -application approval-                                       " << endl;
   
        cout << "=======================================================================================================" << endl << endl;

        WriteInColor(11, "                       +----------------------------------------------------------+\n"); //start here, the text color will be
        WriteInColor(11, "                       | INSTRUCTION :                                            |\n");
        WriteInColor(11, "                       | Move arrow keys (Up, Down, Left, Right) to move the      |\n");
        WriteInColor(11, "                       | selection and press ENTER key to select                  |\n");
        WriteInColor(11, "                       +----------------------------------------------------------+\n");
        WriteInColor(7, "\n"); // change back the next text colour to white

        res = mysql_store_result(conn);
        if (res->row_count == 1) { 
            while (row = mysql_fetch_row(res)) { //assign variable
                studentID = row[0]; 
                student_username = row[1];  
                ic_num = row[2]; 
                student_fullname = row[8];
                work_exp = row[13];
                cgpa = row[20];
            }
        }
        //CASTING, CHANGE STRING TO INT
        stringstream q(cgpa); //CGPA
        q >> doubleCGPA;
        stringstream w(work_exp); //WORK EXPERIENCE
        w >> intWork_exp;
        //End of CASTING, CHANGE STRING TO INT
        cout << setw(98) << "=========================================================================================" << endl;
        cout << setw(98) << "|                                      STUDENT INFO                                     |" << endl;
        cout << setw(98) << "=========================================================================================" << endl;
        cout << setw(32) << right << "| Student ID        :  " << setw(35) << left; WriteInColor(6, studentID); WriteInColor(7, ""); cout << setw(31) << right << " |" << endl;
        cout << setw(98) << "|---------------------------------------------------------------------------------------|" << endl;
        cout << setw(32) << right << "| Fullname          :  " << setw(35) << left; WriteInColor(6, student_fullname); WriteInColor(7, ""); cout << setw(31) << right << " |" << endl;
        cout << setw(98) << "|---------------------------------------------------------------------------------------|" << endl;
        cout << setw(32) << right << "| Username          :  " << setw(35) << left; WriteInColor(6, student_username); WriteInColor(7, ""); cout << setw(31) << right << " |" << endl;
        cout << setw(98) << "|---------------------------------------------------------------------------------------|" << endl;
        cout << setw(32) << right << "| IC Number         :  " << setw(35) << left; WriteInColor(6, ic_num); WriteInColor(7, ""); cout << setw(31) << right << " |" << endl;
        cout << setw(98) << "|---------------------------------------------------------------------------------------|" << endl;
        cout << setw(32) << right << "| Work Experience   :  " << setw(35) << left; WriteInColor(6, work_exp); WriteInColor(7, ""); cout << setw(31) << right << " |" << endl;
        cout << setw(98) << "|---------------------------------------------------------------------------------------|" << endl;
        cout << setw(32) << right << "| Past Studies CGPA :  " << setw(35) << left; WriteInColor(6, cgpa); WriteInColor(7, ""); cout << setw(31) << right << " |" << endl;
        cout << setw(98) << "=========================================================================================" << endl << endl;

        cout << "============================================================================================================================================================================" << endl;
        cout << "|                                                                        APPLICATION INFO                                                                                  |" << endl;
        cout << "|--------------------------------------------------------------------------------------------------------------------------------------------------------------------------|" << endl;
        cout << "| Course Code | Course Name                                                                      | Required CGPA    | Minimum CGPA | Minimum Work Experience | Eligibility |" << endl;
        cout << "|==========================================================================================================================================================================|" << endl;
        //display course 1
        string facultyQuery1 = "select * from courses where programme_code in(select course1 from application where student_id = '" + studentID + "')"; 
        const char* fQuery1 = facultyQuery1.c_str();
        qstate = mysql_query(conn, fQuery1);
        if (!qstate) {
            res = mysql_store_result(conn);
            while (row = mysql_fetch_row(res)) {
                recommendedCGPA = row[4];
                minimumCGPA = row[5];
                minimumWork_exp = row[6];
                //CASTING, CHANGE STRING TO INT
                stringstream x(recommendedCGPA); //Recommended CGPA
                double recomendCGPA = 0;
                x >> recomendCGPA;

                stringstream y(minimumCGPA); //Minimum CGPA
                double minCGPA = 0;
                y >> minCGPA;

                stringstream z(minimumWork_exp); //Minmimum Work Experience
                double minWorkExp = 0;
                z >> minWorkExp;
                // END OF CASTING, CHANGE STRING TO INT
                if (doubleCGPA >= recomendCGPA) {
                    cout << left << "| " << setw(11) << row[2] << " | " << setw(81) << row[3] << "| " << setw(16) << recommendedCGPA << " | " << setw(12) << minimumCGPA << " | " << setw(24) << minimumWork_exp << "| " << setw(12); WriteInColor(10,"YES"); WriteInColor(7,""); cout << "|" << endl;
                    cout << "|--------------------------------------------------------------------------------------------------------------------------------------------------------------------------|" << endl;
                }
                else if( ((doubleCGPA < recomendCGPA) && (doubleCGPA >= minCGPA)) && (intWork_exp >= minWorkExp) ){
                    cout << left << "| " << setw(11) << row[2] << " | " << setw(81) << row[3] << "| " << setw(16) << recommendedCGPA << " | " << setw(12) << minimumCGPA << " | " << setw(24) << minimumWork_exp << "| " << setw(12); WriteInColor(14, "YES"); WriteInColor(7,""); cout << "|" << endl;
                    cout << "|--------------------------------------------------------------------------------------------------------------------------------------------------------------------------|" << endl;
                }
                else {
                    cout << left << "| " << setw(11) << row[2] << " | " << setw(81) << row[3] << "| " << setw(16) << recommendedCGPA << " | " << setw(12) << minimumCGPA << " | " << setw(24) << minimumWork_exp << "| " << setw(12); WriteInColor(12, "NO"); WriteInColor(7, ""); cout << "|" << endl;
                    cout << "|--------------------------------------------------------------------------------------------------------------------------------------------------------------------------|" << endl;
                    course1 = row[2];
                    count++;
                }
            }
        }
        //display course 2
        string facultyQuery2 = "select * from courses where programme_code in(select course2 from application where student_id = '" + studentID + "')";
        const char* fQuery2 = facultyQuery2.c_str();
        qstate = mysql_query(conn, fQuery2);
        if (!qstate) {
            res = mysql_store_result(conn);
            while (row = mysql_fetch_row(res)) {
                recommendedCGPA = row[4];
                minimumCGPA = row[5];
                minimumWork_exp = row[6];
                //CASTING, CHANGE STRING TO INT
                stringstream x(recommendedCGPA); //Recommended CGPA
                double recomendCGPA = 0;
                x >> recomendCGPA;

                stringstream y(minimumCGPA); //Minimum CGPA
                double minCGPA = 0;
                y >> minCGPA;

                stringstream z(minimumWork_exp); //Minmimum Work Experience
                double minWorkExp = 0;
                z >> minWorkExp;
                // END OF CASTING, CHANGE STRING TO INT
                if (doubleCGPA >= recomendCGPA) {
                    cout << left << "| " << setw(11) << row[2] << " | " << setw(81) << row[3] << "| " << setw(16) << recommendedCGPA << " | " << setw(12) << minimumCGPA << " | " << setw(24) << minimumWork_exp << "| " << setw(12); WriteInColor(10, "YES"); WriteInColor(7, ""); cout << "|" << endl;
                    cout << "|--------------------------------------------------------------------------------------------------------------------------------------------------------------------------|" << endl;
                }
                else if (((doubleCGPA < recomendCGPA) && (doubleCGPA >= minCGPA)) && (intWork_exp >= minWorkExp)) {
                    cout << left << "| " << setw(11) << row[2] << " | " << setw(81) << row[3] << "| " << setw(16) << recommendedCGPA << " | " << setw(12) << minimumCGPA << " | " << setw(24) << minimumWork_exp << "| " << setw(12); WriteInColor(14, "YES"); WriteInColor(7, ""); cout << "|" << endl;
                    cout << "|--------------------------------------------------------------------------------------------------------------------------------------------------------------------------|" << endl;
                }
                else {
                    cout << left << "| " << setw(11) << row[2] << " | " << setw(81) << row[3] << "| " << setw(16) << recommendedCGPA << " | " << setw(12) << minimumCGPA << " | " << setw(24) << minimumWork_exp << "| " << setw(12); WriteInColor(12, "NO"); WriteInColor(7, ""); cout << "|" << endl;
                    cout << "|--------------------------------------------------------------------------------------------------------------------------------------------------------------------------|" << endl;
                    course2 = row[2];
                    count++;
                }
            }
        }
        //display course 3
        string facultyQuery3 = "select * from courses where programme_code in(select course3 from application where student_id = '" + studentID + "')";
        const char* fQuery3 = facultyQuery3.c_str();
        qstate = mysql_query(conn, fQuery3);
        if (!qstate) {
            res = mysql_store_result(conn);
            while (row = mysql_fetch_row(res)) {
                recommendedCGPA = row[4];
                minimumCGPA = row[5];
                minimumWork_exp = row[6];
                //CASTING, CHANGE STRING TO INT
                stringstream x(recommendedCGPA); //Recommended CGPA
                double recomendCGPA = 0;
                x >> recomendCGPA;

                stringstream y(minimumCGPA); //Minimum CGPA
                double minCGPA = 0;
                y >> minCGPA;

                stringstream z(minimumWork_exp); //Minmimum Work Experience
                double minWorkExp = 0;
                z >> minWorkExp;
                // END OF CASTING, CHANGE STRING TO INT
                if (doubleCGPA >= recomendCGPA) { //doubleCGPA
                    cout << left << "| " << setw(11) << row[2] << " | " << setw(81) << row[3] << "| " << setw(16) << recommendedCGPA << " | " << setw(12) << minimumCGPA << " | " << setw(24) << minimumWork_exp << "| " << setw(12); WriteInColor(10, "YES"); WriteInColor(7, ""); cout << "|" << endl;
                    cout << "============================================================================================================================================================================" << endl << right << endl;
                }
                else if (((doubleCGPA < recomendCGPA) && (doubleCGPA >= minCGPA)) && (intWork_exp >= minWorkExp)) {
                    cout << left << "| " << setw(11) << row[2] << " | " << setw(81) << row[3] << "| " << setw(16) << recommendedCGPA << " | " << setw(12) << minimumCGPA << " | " << setw(24) << minimumWork_exp << "| " << setw(12); WriteInColor(14, "YES"); WriteInColor(7, ""); cout << "|" << endl;
                    cout << "============================================================================================================================================================================" << endl << right << endl;
                }
                else {
                    cout << left << "| " << setw(11) << row[2] << " | " << setw(81) << row[3] << "| " << setw(16) << recommendedCGPA << " | " << setw(12) << minimumCGPA << " | " << setw(24) << minimumWork_exp << "| " << setw(12); WriteInColor(12, "NO"); WriteInColor(7, ""); cout << "|" << endl;
                    cout << "============================================================================================================================================================================" << endl << right << endl;
                    course3 = row[2];
                    count++;
                }
            }
        }

        if (count == 3) {
            string updateAllFail = "update studentdetails set make_application=2 where student_id = '" + studentID + "'";  //make_application = 2 = approved/disapproved
            const char* uafQuery = updateAllFail.c_str();
            qstate = mysql_query(conn, uafQuery);
            if (!qstate) {
                cout << setw(42) << "THIS STUDENT IS ";  WriteInColor(12, "NOT ELIGIBLE"); WriteInColor(7, ""); cout << " FOR ANY OF THE COURSES" << endl << endl;
            }
            else {
                cout << "Query Execution Problem! MySQL Error #" << mysql_errno(conn) << endl;
            }
        }
        else {
            enterCourseCode:
            do {
                cout << setw(62) << "Enter course code for approval ==> ";
                cin >> approvedCourse;
                if ((approvedCourse == course1) || (approvedCourse == course2) || (approvedCourse == course3)) { //IF INPUT NOT ELIGIBLE COURSES
                    cout << setw(56) << "You cannot approve this course as the student is "; WriteInColor(12, "NOT ELIGIBLE"); WriteInColor(7, ""); cout << " for this course." << endl << endl;
                }
            } while ((approvedCourse == course1) || (approvedCourse == course2) || (approvedCourse == course3));

            string checkCourse = "select course1, course2, course3 from application where student_id = '" + studentID + "'";
            const char* ccQuery = checkCourse.c_str();
            qstate = mysql_query(conn, ccQuery);
            if (!qstate) {
                res = mysql_store_result(conn);
                while (row = mysql_fetch_row(res)) {
                    if ((approvedCourse != row[0]) && (approvedCourse != row[1]) && (approvedCourse != row[2])) { //INPUT COURSES WHICH ISN'T THE STUDENT CHOICES
                        cout << setw(79) << "Please select the correct course code based on student's application" << endl << endl;
                        goto enterCourseCode;
                    }
                    else { //WHEN INPUT COURSES IS ONE OF STUDENT'S COURSES CHOICES
                        string updateResult = "update studentdetails set make_application = 2,application_result = '"
                            + approvedCourse + "' where student_id = '" + studentID + "'";  //make_application = 2 = approved/disapproved
                        const char* urQuery = updateResult.c_str();
                        qstate = mysql_query(conn, urQuery);
                        if (!qstate) {
                            string updateResult = "update courses set approvedStudent = approvedStudent + 1 where programme_code = '" + approvedCourse + "'";  //increment approved student
                            const char* urQuery = updateResult.c_str();
                            qstate = mysql_query(conn, urQuery);
                            if (!qstate) {
                                cout << endl << setw(55) << "COURSE APPROVED" << endl;
                            }
                            else {
                                cout << "Query Execution Problem! MySQL Error #" << mysql_errno(conn) << endl;
                            }
                        }
                        else {
                            cout << "Query Execution Problem! MySQL Error #" << mysql_errno(conn) << endl;
                        }
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
}
//end of application approval function