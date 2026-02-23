#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

/* =========================
        STUDENT CLASS
========================= */
class Student {
public:
    string indexNumber;
    string name;

    Student() {}
    Student(string idx, string nm) {
        indexNumber = idx;
        name = nm;
    }
};

/* =========================
     GLOBAL FUNCTIONS
========================= */

vector<Student> loadStudents() {
    vector<Student> students;
    ifstream file("students.txt");
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string idx, name;

        getline(ss, idx, ',');
        getline(ss, name);

        students.push_back(Student(idx, name));
    }

    file.close();
    return students;
}

void registerStudent() {
    string idx, name;

    cout << "\nEnter Index Number: ";
    cin >> idx;
    cin.ignore();

    cout << "Enter Full Name: ";
    getline(cin, name);

    ofstream file("students.txt", ios::app);
    file << idx << "," << name << endl;
    file.close();

    cout << "\nStudent Registered Successfully!\n";
}

void viewStudents() {
    vector<Student> students = loadStudents();

    cout << "\n===== REGISTERED STUDENTS =====\n";
    for (int i = 0; i < students.size(); i++) {
        cout << students[i].indexNumber 
             << " - " 
             << students[i].name << endl;
    }
}

void searchStudent() {
    vector<Student> students = loadStudents();
    string idx;

    cout << "\nEnter Index Number to Search: ";
    cin >> idx;

    bool found = false;

    for (int i = 0; i < students.size(); i++) {
        if (students[i].indexNumber == idx) {
            cout << "\nStudent Found:\n";
            cout << students[i].indexNumber 
                 << " - " 
                 << students[i].name << endl;
            found = true;
        }
    }

    if (!found)
        cout << "Student not found!\n";
}

void createSession() {
    string courseCode, date;
    vector<Student> students = loadStudents();

    cout << "\nEnter Course Code: ";
    cin >> courseCode;

    cout << "Enter Date (YYYY_MM_DD): ";
    cin >> date;

    string fileName = "session_" + courseCode + "_" + date + ".txt";

    ofstream file(fileName);

    for (int i = 0; i < students.size(); i++) {
        file << students[i].indexNumber 
             << "," 
             << students[i].name 
             << ",Not Marked" << endl;
    }

    file.close();

    cout << "\nSession Created Successfully!\n";
}

void markAttendance() {
    string courseCode, date;

    cout << "\nEnter Course Code: ";
    cin >> courseCode;

    cout << "Enter Date (YYYY_MM_DD): ";
    cin >> date;

    string fileName = "session_" + courseCode + "_" + date + ".txt";

    ifstream file(fileName);
    if (!file) {
        cout << "Session file not found!\n";
        return;
    }

    vector<string> records;
    string line;

    while (getline(file, line)) {
        records.push_back(line);
    }
    file.close();

    ofstream outFile(fileName);

    for (int i = 0; i < records.size(); i++) {
        stringstream ss(records[i]);
        string idx, name, status;

        getline(ss, idx, ',');
        getline(ss, name, ',');
        getline(ss, status);

        cout << "\nMark attendance for "
             << name << " (" << idx << ")\n";
        cout << "1. Present\n2. Absent\n3. Late\nChoice: ";

        int choice;
        cin >> choice;

        if (choice == 1) status = "Present";
        else if (choice == 2) status = "Absent";
        else status = "Late";

        outFile << idx << "," << name << "," << status << endl;
    }

    outFile.close();
    cout << "\nAttendance Marked Successfully!\n";
}

void viewReport() {
    string courseCode, date;

    cout << "\nEnter Course Code: ";
    cin >> courseCode;

    cout << "Enter Date (YYYY_MM_DD): ";
    cin >> date;

    string fileName = "session_" + courseCode + "_" + date + ".txt";

    ifstream file(fileName);
    if (!file) {
        cout << "Session file not found!\n";
        return;
    }

    string line;
    int present = 0, absent = 0, late = 0;

    cout << "\n===== ATTENDANCE REPORT =====\n";

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

int main() {
    int choice;

    do {
        cout << "\n==============================\n";
        cout << " DIGITAL ATTENDANCE SYSTEM\n";
        cout << "==============================\n";
        cout << "1. Register Student\n";
        cout << "2. View Students\n";
        cout << "3. Search Student\n";
        cout << "4. Create Session\n";
        cout << "5. Mark Attendance\n";
        cout << "6. View Report\n";
        cout << "0. Exit\n";
        cout << "Choose Option: ";
        cin >> choice;

        switch (choice) {
            case 1: registerStudent(); break;
            case 2: viewStudents(); break;
            case 3: searchStudent(); break;
            case 4: createSession(); break;
            case 5: markAttendance(); break;
            case 6: viewReport(); break;
            case 0: cout << "Exiting Program...\n"; break;
            default: cout << "Invalid Choice!\n";
        }

    } while (choice != 0);

    return 0;
}
