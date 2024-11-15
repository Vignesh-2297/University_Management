#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include<fstream>

using namespace std;

// Faculty class to store faculty details
class Faculty {
public:
    string facultyCode;
    string facultyName;
    string department;

public:
    Faculty(string code, string name, string dept)
        : facultyCode(code), facultyName(name), department(dept) {}

    void displayInfo() const {
        cout << "Faculty Code: " << facultyCode << endl;
        cout << "Faculty Name: " << facultyName << endl;
        cout << "Department: " << department << endl;
    }

    string getFacultyCode() const {
        return facultyCode;
    }

    string generateAttendanceCode() const {
        string code;
        static const char characters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
        for (int i = 0; i < 6; ++i) {
            code += characters[rand() % (sizeof(characters) - 1)];
        }
        return code;
    }
};

class Subject {
public:
    string name;
    int credits;
    int marks;
    string grade;
    int points;
    string result;
    int totalClasses;
    int attendedClasses;

    Subject(string name, int credits, int totalClasses = 0, int attendedClasses = 0)
        : name(name), credits(credits), marks(0), grade(""), points(0), result("PASS"),
          totalClasses(totalClasses), attendedClasses(attendedClasses) {}

    void assignGrade() {
        if (marks >= 91) { grade = "O"; points = 10; }
        else if (marks >= 81) { grade = "A+"; points = 9; }
        else if (marks >= 71) { grade = "A"; points = 8; }
        else if (marks >= 61) { grade = "B+"; points = 7; }
        else if (marks >= 51) { grade = "B"; points = 6; }
        else if (marks >= 41) { grade = "C"; points = 5; }
        else { grade = "F"; points = 0; result = "FAIL"; }
    }

    void calculateAttendancePercentage() {
        if (totalClasses > 0) {
            float attendancePercentage = (static_cast<float>(attendedClasses) / totalClasses) * 100;
            cout << "Attendance Percentage for " << name << ": " << attendancePercentage << "%" << endl;
        }
    }

    void enterAttendance() {
        cout << "Enter total number of classes held for " << name << ": ";
        cin >> totalClasses;
        cout << "Enter number of classes attended: ";
        cin >> attendedClasses;
        calculateAttendancePercentage();
    }
};

class Student {
public:
    string name;
    string rollNo;

    Student(string name, string rollNo) : name(name), rollNo(rollNo) {}

    void displayStudentDetails() {
        cout << "Student: " << name << " (" << rollNo << ")\n";
    }
};

class Course {
public:
    vector<Subject> subjects;

    // Constructor to initialize subjects based on the semester
    Course(int semesterNo) {
        switch (semesterNo) {
            case 1:
                subjects = { Subject("Engineering Physics", 3, 50),
                    Subject("Calculus for Engineers", 3, 50),
                    Subject("C Programming", 4, 50),
                    Subject("Analytical Reasoning", 3, 50),
                    Subject("Environmental Science", 2, 50),
                    Subject("Emerging Technologies", 2, 50)
                    };
                break;
            case 2:
                subjects = { Subject("Ethics and Human Values", 2, 50),
                    Subject("Economics and Management", 3, 50),
                    Subject("Data Structures", 4, 50),
                    Subject("Basics of EEE", 3, 50),
                    Subject("Entrepreneurial Mindset", 2, 50),
                    Subject("Linear Algebra and DE", 3, 50)
                    };
                break;
            case 3:
                subjects = { Subject("OOPS with C++", 4, 50),
                    Subject("DAA", 4, 50),
                    Subject("(Minor-1)", 3, 50),
                    Subject("Discrete Mathematics", 3, 50),
                    Subject("Digital Electronics", 3, 50),
                    Subject("Problem Solving Skills", 2, 50)
                    };
                break;
            case 4:
                subjects = {Subject("Web Technology", 4, 50),
                    Subject("Python", 2, 50),
                    Subject("DBMS", 4, 50),
                    Subject("(Minor-2)", 3, 50),
                    Subject("Thinking & Creative Skills", 2, 50),
                    Subject("Probability & Statistics", 3, 50)
                    };
                break;
            case 5:
                subjects = {Subject("Computer Networks", 4, 50),
                    Subject("(Minor-3)", 3, 50),
                    Subject("Machine Learning", 4, 50),
                    Subject("Operating Systems", 4, 50),
                    Subject("Automata & Compiler Design", 3, 50),
                    Subject("Computer Architecture", 4, 50)
                    };
                break;
            case 6:
                subjects = {Subject("Software Engineering", 4, 50),
                    Subject("(Minor-4)", 3, 50),
                    Subject("Core-Elective(1)", 3, 50),
                    Subject("Stream Elective(1)", 4, 50),
                    Subject("App Development (JAVA)", 4, 50),
                    Subject("Stream Elective(2)", 4, 50)
                    };
                break;
            case 7:
                subjects = {Subject("Internship/Project", 4, 50),
                    Subject("(Minor-5)", 3, 50),
                    Subject("Core-Elective(2)", 3, 50),
                    Subject("Stream Elective(3)", 4, 50),
                    Subject("Stream Elective(4)", 4, 50),
                    Subject("Mock Interview Training", 3, 50)
                    };
                break;
            case 8:
                subjects = {Subject("Major Project", 12, 50)
                };
                break;
            default:
                cout << "Invalid semester number.\n";
                break;
        }
    }

    void displayCourses() {
        cout << left << setw(30) << "COURSE NAME" << setw(10) << "CREDITS\n";
        cout << "------------------------    -------\n";
        for (int i = 0; i < subjects.size(); ++i) {
            cout << left << setw(3) << i + 1 << setw(30) << subjects[i].name << setw(10) << subjects[i].credits << "\n";
        }
    }

    void enterMarks() {
        for (auto& subject : subjects) {
            cout << "Enter marks for " << subject.name << ": ";
            cin >> subject.marks;
            subject.assignGrade();
        }
    }

    float calculateCGPA() {
        int totalCredits = 0;
        float weightedPoints = 0;

        for (auto& subject : subjects) {
            totalCredits += subject.credits;
            weightedPoints += subject.points * subject.credits;
        }

        return weightedPoints / totalCredits;
    }

    void displayResults(int semesterNo) {
        cout << "SEMESTER " << semesterNo << " RESULTS:\n";
        cout << left << setw(30) << "Subject Description" << setw(10) << "Credit" << setw(10) << "Grade" << "Result\n";
        cout << "----------------------      ------      -----      ------\n";
        for (auto& subject : subjects) {
            cout << left << setw(30) << subject.name << setw(10) << subject.credits << setw(10) << subject.grade << subject.result << "\n";
        }
    }

    void enterAttendance() {
        for (auto& subject : subjects) {
            subject.enterAttendance();
        }
    }
};
// Function to save faculty details to a file
void saveFacultyData(const vector<Faculty>& facultyList) {
    ofstream outFile("faculty_data.txt");
    if (outFile.is_open()) {
        for (const auto& faculty : facultyList) {
            outFile << faculty.getFacultyCode() << ","
                    << faculty.facultyName << ","
                    << faculty.department << "\n";
        }
        outFile.close();
    } else {
        cout << "Unable to open file for saving faculty data.\n";
    }
}

// Function to load faculty details from a file
void loadFacultyData(vector<Faculty>& facultyList) {
    ifstream inFile("faculty_data.txt");
    string code, name, dept;

    while (getline(inFile, code, ',')) {
        getline(inFile, name, ',');
        getline(inFile, dept);
        facultyList.push_back(Faculty(code, name, dept));
    }

    inFile.close();
}

// Function to save student details and course data to a file
void saveStudentData(const Student& student, const Course& course) {
    ofstream outFile(student.rollNo + "_data.txt");
    if (outFile.is_open()) {
        outFile << student.name << "\n" << student.rollNo << "\n";
        for (const auto& subject : course.subjects) {
            outFile << subject.name << ","
                    << subject.marks << ","
                    << subject.grade << ","
                    << subject.attendedClasses << ","
                    << subject.totalClasses << "\n";
        }
        outFile.close();
    } else {
        cout << "Unable to open file for saving student data.\n";
    }
}

// Function to load student details and course data from a file
void loadStudentData(Student& student, Course& course) {
    ifstream inFile(student.rollNo + "_data.txt");
    string subjectName, grade;
    int marks, attended, total;

    if (inFile.is_open()) {
        getline(inFile, student.name);
        getline(inFile, student.rollNo);
        while (getline(inFile, subjectName, ',')) {
            inFile >> marks;
            inFile.ignore();
            getline(inFile, grade, ',');
            inFile >> attended >> total;
            course.subjects.push_back(Subject(subjectName, 3, total, attended)); // Assuming 3 credits for all subjects
            course.subjects.back().marks = marks;
            course.subjects.back().grade = grade;
        }
        inFile.close();
    } else {
        cout << "Unable to open file for loading student data.\n";
    }
}


int main() {
    srand(time(0));
    vector<Faculty> facultyList;
    int mainChoice, choice;
    string searchCode;
    facultyList.push_back(Faculty("F001", "Dr. Smith", "Computer Science"));
    facultyList.push_back(Faculty("F002", "Prof. John", "Mathematics"));

    do {
        cout << "\nUniversity Management System\n";
        cout << "1. Faculty Options\n";
        cout << "2. Student Options\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> mainChoice;

        switch (mainChoice) {
            case 1:
                do {
                    cout << "\nFaculty Management\n";
                    cout << "1. Add Faculty\n";
                    cout << "2. Display All Faculty\n";
                    cout << "3. Generate Attendance Code\n";
                    cout << "4. Back to Main Menu\n";
                    cout << "Enter your choice: ";
                    cin >> choice;

                    switch (choice) {
                        case 1: {
                            string code, name, dept;
                            cout << "Enter Faculty Code: ";
                            cin >> code;
                            cout << "Enter Faculty Name: ";
                            cin.ignore();
                            getline(cin, name);
                            cout << "Enter Department: ";
                            getline(cin, dept);

                            Faculty newFaculty(code, name, dept);
                            facultyList.push_back(newFaculty);
                            cout << "Faculty added successfully!\n";
                            break;
                        }
                        case 2:
                            if (facultyList.empty()) {
                                cout << "No faculty members found.\n";
                            } else {
                                for (const auto& faculty : facultyList) {
                                    faculty.displayInfo();
                                    cout << "-------------------------\n";
                                }
                            }
                            break;
                        case 3:
                            cout << "Enter Faculty Code to generate attendance code: ";
                            cin >> searchCode;
                            for (const auto& faculty : facultyList) {
                                if (faculty.getFacultyCode() == searchCode) {
                                    faculty.displayInfo();
                                    cout << "Attendance Code: " << faculty.generateAttendanceCode() << endl;
                                    break;
                                }
                            }
                            break;
                        case 4:
                            cout << "Returning to Main Menu...\n";
                            break;
                        default:
                            cout << "Invalid choice! Please try again.\n";
                    }
                } while (choice != 4);
                break;

            case 2: {
                string name, rollNo;
                int semesterNo;

                cout << "Enter your name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter your Registration Number: ";
                cin >> rollNo;
                cout << "Enter the semester number (1-8): ";
                cin >> semesterNo;

                Student student(name, rollNo);
                Course course(semesterNo);

                do {
                    cout << "\nStudent Management\n";
                    cout << "1. Display Courses\n";
                    cout << "2. Enter Marks\n";
                    cout << "3. Display Results\n";
                    cout << "4. Calculate CGPA\n";
                    cout << "5. Enter Attendance\n";
                    cout << "6. Back to Main Menu\n";
                    cout << "Enter your choice: ";
                    cin >> choice;

                    switch (choice) {
                        case 1:
                            course.displayCourses();
                            break;
                        case 2:
                            course.enterMarks();
                            break;
                        case 3:
                            course.displayResults(semesterNo);
                            break;
                        case 4:
                            cout << "CGPA: " << fixed << setprecision(2) << course.calculateCGPA() << endl;
                            break;
                        case 5:
                            course.enterAttendance();
                            break;
                        case 6:
                            cout << "Returning to Main Menu...\n";
                            break;
                        default:
                            cout << "Invalid choice! Please try again.\n";
                    }
                } while (choice != 6);
                break;
            }

            case 3:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (mainChoice != 3);

    return 0;
}
