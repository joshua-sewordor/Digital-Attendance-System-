# Digital-Attendance-System
This system is designed to replace the traditional paper-based method of taking attendance during hour-based lectures. This system provides a simple, efficient, and reliable digital solution that allows lecturers to manage student records and attendance sessions electronically.
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

/* ================= STUDENT CLASS ================= */

class Student {
public:
    string indexNumber;
    string name;

    Student() {}

    Student(string idx, string nm) {
        indexNumber = idx;
        name = nm;
    }

    void saveToFile() {
        ofstream file("students.txt", ios::app);
        file << indexNumber << "," << name << endl;
        file.close();
    }

    static vector<Student> loadStudents() {
        vector<Student> students;
        ifstream file("students.txt");
        string line;

        while (getline(file, line)) {
            int pos = line.find(",");
            string idx = line.substr(0, pos);
            string nm = line.substr(pos + 1);
            students.push_back(Student(idx, nm));
        }

        file.close();
        return students;
    }
};

/* ================= ATTENDANCE SESSION CLASS ================= */

class AttendanceSession {
public:
    string courseCode;
    string date;
    string startTime;
    int duration;

    AttendanceSession(string cc, string d, string st, int dur) {
        courseCode = cc;
        date = d;
        startTime = st;
        duration = dur;
    }

    string getFileName() {
        return "session_" + courseCode + "_" + date + ".txt";
    }

    void createSessionFile(vector<Student> students) {
        ofstream file(getFileName());

        for (Student s : students) {
            file << s.indexNumber << "," << s.name << ",Not Marked" << endl;
        }

        file.close();
    }

    void markAttendance() {
        vector<string> lines;
        ifstream file(getFileName());
        string line;

        while (getline(file, line)) {
            lines.push_back(line);
        }
        file.close();

        ofstream outFile(getFileName());

        for (string record : lines) {
            int pos1 = record.find(",");
            int pos2 = record.find(",", pos1 + 1);

            string idx = record.substr(0, pos1);
            string name = record.substr(pos1 + 1, pos2 - pos1 - 1);

            cout << "\nMark attendance for " << name 
                 << " (" << idx << ")" << endl;
            cout << "1. Present  2. Absent  3. Late: ";
            int choice;
            cin >> choice;

            string status;

            if (choice == 1) status = "Present";
            else if (choice == 2) status = "Absent";
            else status = "Late";

            outFile << idx << "," << name << "," << status << endl;
        }

        outFile.close();
        cout << "\nAttendance marked successfully!\n";
    }

    void displayReport() {
        ifstream file(getFileName());
        string line;
        int present = 0, absent = 0, late = 0;

        cout << "\n===== Attendance Report =====\n";

        while (getline(file, line)) {
            cout << line << endl;

            if (line.find("Present") != string::npos) present++;
            if (line.find("Absent") != string::npos) absent++;
            if (line.find("Late") != string::npos) late++;
        }

        file.close();

        cout << "\nSummary:\n";
        cout << "Present: " << present << endl;
        cout << "Absent : " << absent << endl;
        cout << "Late   : " << late << endl;
    }
};

/* ================= MAIN MENU ================= */

void registerStudent() {
    string idx, name;
    cout << "\nEnter Index Number: ";
    cin >> idx;
    cin.ignore();
    cout << "Enter Name: ";
    getline(cin, name);

    Student s(idx, name);
    s.saveToFile();

    cout << "Student registered successfully!\n";
}

void viewStudents() {
    vector<Student> students = Student::loadStudents();

    cout << "\n===== Registered Students =====\n";

    for (Student s : students) {
        cout << s.indexNumber << " - " << s.name << endl;
    }
}

void createSession() {
    string cc, date, startTime;
    int duration;

    cout << "\nEnter Course Code: ";
    cin >> cc;
    cout << "Enter Date (YYYY_MM_DD): ";
    cin >> date;
    cout << "Enter Start Time (HH:MM): ";
    cin >> startTime;
    cout << "Enter Duration (minutes): ";
    cin >> duration;

    vector<Student> students = Student::loadStudents();

    AttendanceSession session(cc, date, startTime, duration);
    session.createSessionFile(students);

    cout << "Session created successfully!\n";
}

void markSessionAttendance() {
    string cc, date;

    cout << "\nEnter Course Code: ";
    cin >> cc;
    cout << "Enter Date (YYYY_MM_DD): ";
    cin >> date;

    AttendanceSession session(cc, date, "", 0);
    session.markAttendance();
}

void viewSessionReport() {
    string cc, date;

    cout << "\nEnter Course Code: ";
    cin >> cc;
    cout << "Enter Date (YYYY_MM_DD): ";
    cin >> date;

    AttendanceSession session(cc, date, "", 0);
    session.displayReport();
}

int main() {
    int choice;

    do {
        cout << "\n===== DIGITAL ATTENDANCE SYSTEM =====\n";
        cout << "1. Register Student\n";
        cout << "2. View Students\n";
        cout << "3. Create Lecture Session\n";
        cout << "4. Mark Attendance\n";
        cout << "5. View Attendance Report\n";
        cout << "0. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
        case 1: registerStudent(); break;
        case 2: viewStudents(); break;
        case 3: createSession(); break;
        case 4: markSessionAttendance(); break;
        case 5: viewSessionReport(); break;
        case 0: cout << "Exiting program...\n"; break;
        default: cout << "Invalid choice!\n";
        }

    } while (choice != 0);

    return 0;
}
