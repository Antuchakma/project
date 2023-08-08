#include <iostream>
#include <string>

using namespace std;

class Schedule;

class Ct {
    float date[3]; // 3 = per subject ct number
    string course_name;

public:
    void putdata() {
        for (int i = 0; i < 3; i++) {
            cout << "CT" << " " << i + 1 << "=" << "date=" << date[i] << " ";
        }
        cout << endl;
    }

    friend class Schedule;
    friend void sir_ct(Schedule& s);
};

class Teacher {
    friend class Schedule;
    int ID;
    int time[5][2]; // 5 = number of week, 2 = number of teacher
    string teacher_name;
    string department;
    string course_name;

public:
    Teacher() {}

    Teacher(int i) {
        cout << "Teacher ID=";
        cin >> ID;
        cout << "Teacher name=";
        cin.ignore(); // To consume the newline character left in the stream from previous input
        getline(cin, teacher_name);
        cout << "Teacher department=";
        getline(cin, department);
        cout << "Teacher course name=";
        getline(cin, course_name);
    }

    friend void tea_sche_check(Schedule& s, int ID, string day);
    friend void routine_check(Schedule& s, int ID, string course, string day);
    friend void sir_ct(Schedule& s);
};

class Student {
    int ID;
    string course_name[10]; // course name = teacher number
    float separate_mark[2][3] = {0}; // here 2 is course number, 3 is ct number
    float total_mark[10] = {0}; // 10 = number of course
    string stud_name;
    string enrollment_status;
    string department;

public:
    Student() {}

    Student(int i) {
        cout << "Student ID=";
        cin >> ID;
        cout << "Student name=";
        cin.ignore(); // To consume the newline character left in the stream from previous input
        getline(cin, stud_name);
        cout << "Student Department=";
        getline(cin, department);
    }

    void output() {
        cout << "stud_name=" << stud_name << endl;
        for (int i = 0; i < 2; i++) { // 2 = course number
            cout << "course _name=" << course_name[i] << endl;
            cout << "Seperate mark of ct of " << " " << course_name[i] << " " << "subject:" << endl;
            for (int j = 0; j < 3; j++) { // 3 = per subject ct number
                cout << "CT" << " " << j + 1 << " " << "mark=";
                cout << separate_mark[i][j] << endl;
            }
            cout << "Total_mark of ct " << " " << course_name[i] << "subject:" << total_mark[i] << endl;
        }
    }

    friend void routine_check(Schedule& s, int ID, string course, string day);
    friend class Schedule;
    friend void sir_ct(Schedule& s);
};

class Schedule {
    Teacher about_teacher[10]; // 10 = number of teacher
    Student about_student[10]; // 10 number of student
    string day[5]; // 5 = number of day
    Ct about_ct[10]; // 10 = number of subject

public:
    void getdata();
    friend void tea_sche_check(Schedule& s, int ID, string day);
    friend void routine_check(Schedule& s, int ID, string course, string day);
    friend void sir_ct(Schedule& s);
    void putdata() {
        for (int i = 0; i < 2; i++) { // 2 = number of subject = number of teacher
            cout << "Course name:" << " " << about_ct[i].course_name << endl;
            about_ct[i].putdata();
        }

        for (int i = 0; i < 2; i++) { // 2 = number of student
            about_student[i].output();
        }
    }
};

void tea_sche_check(Schedule& s, int ID, string day) {
    int c = 0;
    for (int i = 0; i < 5; i++) { // 5 = number of day
        if (day == s.day[i]) {
            for (int j = 0; j < 2; j++) { // 2 = number of teacher = number of student
                if (ID == s.about_teacher[j].ID) {
                    if (s.about_teacher[j].time[i][j] >= 8 && s.about_teacher[j].time[i][j] <= 13) {
                        cout << "class time=" << s.about_teacher[j].time[i][j] << endl;
                        c = 1;
                        break;
                    }
                }
            }
        } else if (c == 1)
            break;
        else if (i == 4) {
            cout << "No class today" << endl;
        }
    }
}

void routine_check(Schedule& s, int ID, string course, string day) {
    int c = 0;
    for (int i = 0; i < 5; i++) {
        if (day == s.day[i]) {
            for (int j = 0; j < 2; j++) {
                if (ID == s.about_student[j].ID) {
                    if (course == s.about_teacher[j].course_name) {
                        if (s.about_teacher[j].time[i][j] >= 8 && s.about_teacher[j].time[i][j] <= 13) {
                            cout << "Teacher name=" << s.about_teacher[j].teacher_name << " " << "Class time" << s.about_teacher[j].time[i][j] << endl;
                            c = 1;
                            break;
                        }
                    }
                }
            }
        } else if (c == 1)
            break;
        else if (i == 4)
            cout << "no class" << endl;
    }
}

void Schedule::getdata() {
    for (int i = 0; i < 2; i++) { // 2 = number of teachers
        cout << "\nInformation About Teacher " << i + 1 << endl;
        about_teacher[i] = Teacher(i);
        getchar();
    }

    for (int i = 0; i < 2; i++) { // 2 = number of students
        cout << "\nInformation About Student " << i + 1 << endl;
        about_student[i] = Student(i);
        getchar();
    }

    for (int i = 0; i < 5; i++) { // 5 = number of days
        cout << "\nDay of the week " << i + 1 << ": ";
        cin >> day[i];
        getchar();
        for (int j = 0; j < 2; j++) { // 2 = number of teachers
            cout << "Time of Teacher " << about_teacher[j].ID << " on " << day[i] << ": ";
            cin >> about_teacher[j].time[i][j];
        }
    }

    cout << endl;
    for (int i = 0; i < 5; i++) { // 5 = number of days
        cout << "Day " << i + 1 << ": " << day[i];
        for (int j = 0; j < 2; j++)
            cout << " | Teacher " << about_teacher[j].ID << " - Time: " << about_teacher[j].time[i][j];
        cout << endl;
    }
}

void sir_ct(Schedule& s) {
    for (int i = 0; i < 2; i++) { // should be changed. 2 = koto subject ct = number of teachers
        s.about_ct[i].course_name = s.about_teacher[i].course_name;
        for (int k = 0; k < 2; k++) { // k = per student koto subject pabe = number of teachers
            s.about_student[i].course_name[k] = s.about_teacher[k].course_name;
        }

        cout << "Entering Ct date of" << " " << s.about_teacher[i].course_name << ":" << endl;
        for (int j = 0; j < 3; j++) {
            cout << "CT" << " " << j + 1 << ":";
            cin >> s.about_ct[i].date[j];
        }

        for (int l = 0; l < 2; l++) { // l = student number
            cout << "Entering " << " " << s.about_teacher[i].course_name << " " << "CT mark of" << " " << s.about_student[l].stud_name << ":" << endl;
            for (int j = 0; j < 3; j++) { // j = per student er separate ct number
                cout << "CT" << j + 1 << ":";
                cin >> s.about_student[l].separate_mark[i][j]; // l = different subject = number of students
                s.about_student[l].total_mark[i] = s.about_student[i].total_mark[i] + s.about_student[l].separate_mark[l][j];
            }
        }
    }
}

int main() {
    Schedule about_schedule;
    about_schedule.getdata();

    while (true) {
        char c;
        cout << "\nDo you want information about your class? (y/n): ";
        cin >> c;
        if (c == 'y' || c == 'Y') {
            cout << "For teacher class information" << endl;
            int ID;
            string day;
            cout << "Input Teacher ID: ";
            cin >> ID;
            cout << "Input the name of the day: ";
            cin >> day;
            getchar();
            tea_sche_check(about_schedule, ID, day);
        } else {
            break;
        }
    }

    while (true) {
        char ch;
        cout << "\nDo you want information about your routine? (y/n): ";
        cin >> ch;
        if (ch == 'y' || ch == 'Y') {
            cout << "For student class information" << endl;
            int stud_ID;
            string course, day;
            cout << "Enter search student ID: ";
            cin >> stud_ID;
            cout << "Enter search student course: ";
            cin.ignore(); // To consume the newline character left in the stream from previous input
            getline(cin, course);
            cout << "Enter search student class day: ";
            cin >> day;
            routine_check(about_schedule, stud_ID, course, day);
        } else {
            break;
        }
    }

    sir_ct(about_schedule);

    // Display the final schedule information
    cout << "\nFinal Schedule Information:\n";
    about_schedule.putdata();

    return 0;
}
