#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <cmath>
#include <cstdlib>

using namespace std;

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

    // Constructor
    Subject(string name, int credits, int totalClasses = 0, int attendedClasses = 0) 
        : name(name), credits(credits), marks(0), grade(""), points(0), result("PASS"),
          totalClasses(totalClasses), attendedClasses(attendedClasses) {}

    void assignGrade() {
        if (marks >= 91) {
            grade = "O";
            points = 10;
        } else if (marks >= 81) {
            grade = "A+";
            points = 9;
        } else if (marks >= 71) {
            grade = "A";
            points = 8;
        } else if (marks >= 61) {
            grade = "B+";
            points = 7;
        } else if (marks >= 51) {
            grade = "B";
            points = 6;
        } else if (marks >= 41) {
            grade = "C";
            points = 5;
        } else {
            grade = "F";
            points = 0;
            result = "FAIL";
        }
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

    // Constructor
    Student(string name, string rollNo) : name(name), rollNo(rollNo) {}

    void displayStudentDetails() {
        cout << "Student: " << name << " (" << rollNo << ")\n";
    }
};

class Course {
public:
    vector<Subject> subjects;

    // Constructor
    Course(vector<Subject> subjects) : subjects(subjects) {}

    void displayCourses() {
        cout << left << setw(30) << "COURSE NAME" << setw(10) << "CREDITS\n";
        cout << "------------------------------  -------\n";
        for (int i = 0; i < subjects.size(); ++i) {
            cout << left << setw(3) << i + 1 << setw(30) << subjects[i].name << setw(10) << subjects[i].credits << "\n";
        }
    }

    void enterMarks() {
        for (auto& subject : subjects) {
            cout << "Enter marks for " << subject.name << ": ";
            cin >> subject.marks;
            if (subject.marks < 0 || subject.marks > 100) {
                cout << "Invalid marks entered! Exiting program.\n";
                exit(0);
            }
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
        cout << left << setw(25) << "Subject Description" << setw(10) << "Credit" << setw(10) << "Grade" << "Result\n";
        cout << "------------------------    ------    -----    ------\n";
        for (auto& subject : subjects) {
            cout << left << setw(25) << subject.name << setw(10) << subject.credits << setw(10) << subject.grade << subject.result << "\n";
        }
    }

    void enterAttendance() {
        for (auto& subject : subjects) {
            subject.enterAttendance();
        }
    }
};

class Grading {
public:
    static void calculateAndDisplayGPA(Course& course, int semesterNo) {
        course.displayResults(semesterNo);
        float cgpa = course.calculateCGPA();
        cout << fixed << setprecision(3);
        cout << "CGPA for semester " << semesterNo << ": " << cgpa << "\n";
    }
};

class Display {
public:
    static void showCourseDetails(int semesterNo, Course& course, Student& student) {
        cout << "Semester " << semesterNo << " courses for " << student.name << " (" << student.rollNo << "):\n";
        course.displayCourses();
    }

    static void showCompletionMessage() {
        cout << "\nSemester Completed\n";
        cout << "Would you like to know your GPA? Enter 1 for Yes or any other number to Exit: ";
    }
};

class Semester {
public:
    int semesterNo;
    Course course;

    Semester(int semesterNo, Course course) : semesterNo(semesterNo), course(course) {}

    void processSemester(Student& student) {
        Display::showCourseDetails(semesterNo, course, student);
        Display::showCompletionMessage();

        int choice;
        cin >> choice;
        if (choice == 1) {
            course.enterMarks();
            Grading::calculateAndDisplayGPA(course, semesterNo);
        }

        cout << "\nDo you want to enter attendance details? (Enter 1 for Yes, any other key for No): ";
        int attendanceChoice;
        cin >> attendanceChoice;
        if (attendanceChoice == 1) {
            course.enterAttendance();
        }
    }
};

int main() {
    string name, rollNo;
    int semesterNo;

    // Student Input
    cout << "Enter your name: ";
    getline(cin, name);
    cout << "Enter your Registration Number: ";
    cin >> rollNo;

    Student student(name, rollNo);

    cout << "Enter the semester number (1-8): ";
    cin >> semesterNo;

    // Course and Semester data for different semesters
    switch (semesterNo) {
        case 1:
            {
                Course course({
                    Subject("Engineering Physics", 3, 50),
                    Subject("Calculus for Engineers", 3, 50),
                    Subject("C Programming", 4, 50),
                    Subject("Analytical Reasoning", 3, 50),
                    Subject("Environmental Science", 2, 50),
                    Subject("Emerging Technologies", 2, 50)
                });
                Semester semester(semesterNo, course);
                semester.processSemester(student);
                break;
            }

        case 2:
            {
                Course course({
                    Subject("Ethics and Human Values", 2, 50),
                    Subject("Economics and Management", 3, 50),
                    Subject("Data Structures", 4, 50),
                    Subject("Basics of EEE", 3, 50),
                    Subject("Entrepreneurial Mindset", 2, 50),
                    Subject("Linear Algebra and DE", 3, 50)
                });
                Semester semester(semesterNo, course);
                semester.processSemester(student);
                break;
            }

        case 3:
            {
                Course course({
                    Subject("OOPS with C++", 4, 50),
                    Subject("DAA", 4, 50),
                    Subject("(Minor-1)", 3, 50),
                    Subject("Discrete Mathematics", 3, 50),
                    Subject("Digital Electronics", 3, 50),
                    Subject("Problem Solving Skills", 2, 50)
                });
                Semester semester(semesterNo, course);
                semester.processSemester(student);
                break;
            }

        case 4:
            {
                Course course({
                    Subject("Web Technology", 4, 50),
                    Subject("Python", 2, 50),
                    Subject("DBMS", 4, 50),
                    Subject("(Minor-2)", 3, 50),
                    Subject("Thinking & Creative Skills", 2, 50),
                    Subject("Probability & Statistics", 3, 50)
                });
                Semester semester(semesterNo, course);
                semester.processSemester(student);
                break;
            }

        case 5:
            {
                Course course({
                    Subject("Computer Networks", 4, 50),
                    Subject("(Minor-3)", 3, 50),
                    Subject("Machine Learning", 4, 50),
                    Subject("Operating Systems", 4, 50),
                    Subject("Automata & Compiler Design", 3, 50),
                    Subject("Computer Architecture", 4, 50)
                });
                Semester semester(semesterNo, course);
                semester.processSemester(student);
                break;
            }

        case 6:
            {
                Course course({
                    Subject("Software Engineering", 4, 50),
                    Subject("(Minor-4)", 3, 50),
                    Subject("Core-Elective(1)", 3, 50),
                    Subject("Stream Elective(1)", 4, 50),
                    Subject("App Development (JAVA)", 4, 50),
                    Subject("Stream Elective(2)", 4, 50)
                });
                Semester semester(semesterNo, course);
                semester.processSemester(student);
                break;
            }

        case 7:
            {
                Course course({
                    Subject("Internship/Project", 4, 50),
                    Subject("(Minor-5)", 3, 50),
                    Subject("Core-Elective(2)", 3, 50),
                    Subject("Stream Elective(3)", 4, 50),
                    Subject("Stream Elective(4)", 4, 50),
                    Subject("Mock Interview Training", 3, 50)
                });
                Semester semester(semesterNo, course);
                semester.processSemester(student);
                break;
            }

        case 8:
            {
                Course course({ Subject("Major Project", 12, 50) });
                Semester semester(semesterNo, course);
                semester.processSemester(student);
                break;
            }

        default:
            cout << "Invalid semester number. Please enter a valid semester between 1 and 8.\n";
            break;
    }

    return 0;
}