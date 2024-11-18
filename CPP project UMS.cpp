// Online C++ compiler to run C++ program online
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <iomanip>
#include <algorithm>
#include <exception>
#include <fstream>

using namespace std;

// Base Class: Person
class Person {
protected:
    string name, ID, email, password;
public:
    Person() : name(""), ID(""), email(""), password("") {}
    Person(const string& n, const string& i, const string& e, const string& p) 
        : name(n), ID(i), email(e), password(p) {}

    virtual void inputLoginDetails() {
        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter ID: ";
        cin >> ID;
        cin.ignore();
        cout << "Enter Email: ";
        getline(cin, email);
        cout << "Set Password: ";
        cin >> password;
        cin.ignore();
    }

    bool login(const string& id, const string& pass) const {
        return (ID == id && password == pass);
    }

    string getID() const {
        return ID;
    }

    virtual void displayInfo() const {
        cout << "Name: " << name << "\nID: " << ID << "\nEmail: " << email << endl;
    }

    virtual void saveToFile(ofstream& file) const = 0;  // Pure virtual function for saving data
    virtual void loadFromFile(ifstream& file) = 0;      // Pure virtual function for loading data
};

// Derived Class: Student
class Student : public Person {
private:
    vector<string> courses;
    map<string, double> marks;   // courseID -> marks
    map<string, char> grades;   // courseID -> grade
    int attendance;
    double CGPA;

    char calculateGrade(double marks) {
        if (marks >= 90) return 'A';
        if (marks >= 80) return 'B';
        if (marks >= 70) return 'C';
        if (marks >= 60) return 'D';
        return 'F';
    }

    void calculateCGPA() {
        if (grades.empty()) {
            CGPA = 0.0;
            return;
        }

        double gradePoints = 0.0;
        for (const auto& [course, grade] : grades) {
            switch (grade) {
                case 'A': gradePoints += 10.0; break;
                case 'B': gradePoints += 9.0; break;
                case 'C': gradePoints += 8.0; break;
                case 'D': gradePoints += 7.0; break;
                default: gradePoints += 0.0;
            }
        }
        CGPA = gradePoints / grades.size();
    }

public:
    Student() : Person(), attendance(0), CGPA(0.0) {}

    void registerCourse(const string& courseID) {
        if (find(courses.begin(), courses.end(), courseID) == courses.end()) {
            courses.push_back(courseID);
            cout << "Registered for course: " << courseID << endl;
        } else {
            cout << "Already registered for this course." << endl;
        }
    }

    void addMarks(const string& courseID, double courseMarks) {
        if (find(courses.begin(), courses.end(), courseID) == courses.end()) {
            cout << "Student is not registered for course: " << courseID << endl;
            return;
        }
        marks[courseID] = courseMarks;
        grades[courseID] = calculateGrade(courseMarks);
        calculateCGPA();
    }

    void markAttendance(int days) {
        if (days < 0) {
            cout << "Attendance days cannot be negative.\n";
            return;
        }
        attendance += days;
    }

    void viewAccount() const {
        cout << "Welcome, " << name << "!\n";
        cout << "Attendance: " << attendance << " days\n";
        cout << "Registered Courses and Marks:\n";
        for (const auto& course : courses) {
            cout << "  " << course << ": ";
            if (marks.find(course) != marks.end()) {
                cout << "Marks: " << marks.at(course) << ", Grade: " << grades.at(course) << endl;
            } else {
                cout << "Marks not entered yet.\n";
            }
        }
        cout << "CGPA: " << fixed << setprecision(2) << CGPA << endl;
    }

    void saveToFile(ofstream& file) const override {
        file << "Student\n";
        file << name << "\n" << ID << "\n" << email << "\n" << password << "\n";
        file << courses.size() << "\n";
        for (const auto& course : courses) {
            file << course << "\n";
        }
        file << marks.size() << "\n";
        for (const auto& [course, mark] : marks) {
            file << course << " " << mark << "\n";
        }
        file << grades.size() << "\n";
        for (const auto& [course, grade] : grades) {
            file << course << " " << grade << "\n";
        }
        file << attendance << "\n";
        file << CGPA << "\n";
    }

    void loadFromFile(ifstream& file) override {
        file.ignore();
        getline(file, name);
        getline(file, ID);
        getline(file, email);
        getline(file, password);

        int courseCount;
        file >> courseCount;
        courses.clear();
        for (int i = 0; i < courseCount; ++i) {
            string course;
            file >> course;
            courses.push_back(course);
        }

        int marksCount;
        file >> marksCount;
        marks.clear();
        for (int i = 0; i < marksCount; ++i) {
            string course;
            double mark;
            file >> course >> mark;
            marks[course] = mark;
        }

        int gradeCount;
        file >> gradeCount;
        grades.clear();
        for (int i = 0; i < gradeCount; ++i) {
            string course;
            char grade;
            file >> course >> grade;
            grades[course] = grade;
        }

        file >> attendance;
        file >> CGPA;
    }
};

// Derived Class: Faculty
class Faculty : public Person {
private:
    vector<string> assignedCourses;
public:
    Faculty() : Person() {}

    void assignMarks(Student& student, const string& courseID, double marks) {
        student.addMarks(courseID, marks);
        cout << "Marks assigned successfully.\n";
    }

    void assignAttendance(Student& student, int days) {
        student.markAttendance(days);
        cout << "Attendance assigned successfully.\n";
    }

    void inputDetails() {
        Person::inputLoginDetails();
        cout << "Enter number of courses to assign: ";
        int numCourses;
        cin >> numCourses;
        cin.ignore();
        for (int i = 0; i < numCourses; ++i) {
            string course;
            cout << "Enter Course ID for course " << (i + 1) << ": ";
            getline(cin, course);
            assignedCourses.push_back(course);
        }
    }

    void displayInfo() const override {
        Person::displayInfo();
        cout << "Assigned Courses: ";
        for (const auto& course : assignedCourses) cout << course << " ";
        cout << endl;
    }

    void saveToFile(ofstream& file) const override {
        file << "Faculty\n";
        file << name << "\n" << ID << "\n" << email << "\n" << password << "\n";
        file << assignedCourses.size() << "\n";
        for (const auto& course : assignedCourses) {
            file << course << "\n";
        }
    }

    void loadFromFile(ifstream& file) override {
        file.ignore();
        getline(file, name);
        getline(file, ID);
        getline(file, email);
        getline(file, password);

        int courseCount;
        file >> courseCount;
        assignedCourses.clear();
        for (int i = 0; i < courseCount; ++i) {
            string course;
            file >> course;
            assignedCourses.push_back(course);
        }
    }
};

// Main Function
int main() {
    vector<Student> students;
    vector<Faculty> faculties;

    // Load data from files
    ifstream studentFile("students.txt");
    ifstream facultyFile("faculties.txt");

    if (studentFile.is_open()) {
        string line;
        while (getline(studentFile, line)) {
            Student student;
            student.loadFromFile(studentFile);
            students.push_back(student);
        }
        studentFile.close();
    }

    if (facultyFile.is_open()) {
        string line;
        while (getline(facultyFile, line)) {
            Faculty faculty;
            faculty.loadFromFile(facultyFile);
            faculties.push_back(faculty);
        }
        facultyFile.close();
    }

    int choice;
    do {
        cout << "\nWelcome to University Management System\n";
        cout << "1. Add Student\n";
        cout << "2. Add Faculty\n";
        cout << "3. Admin Login\n";
        cout << "4. Student Login\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            Student student;
            cout << "\nEnter Student Details:\n";
            student.inputLoginDetails();
            students.push_back(student);
            cout << "Student added successfully!\n";

        } else if (choice == 2) {
            Faculty faculty;
            cout << "\nEnter Faculty Details:\n";
            faculty.inputDetails();
            faculties.push_back(faculty);
            cout << "Faculty added successfully!\n";

        } else if (choice == 3) {
            string facultyID, password;
            cout << "\nEnter Faculty ID: ";
            cin >> facultyID;
            cout << "Enter Password: ";
            cin >> password;

            auto it = find_if(faculties.begin(), faculties.end(),
                              [&](const Faculty& f) { return f.login(facultyID, password); });
            if (it != faculties.end()) {
                cout << "Login successful!\n";
                int facultyChoice;
                do {
                    cout << "\n1. Assign Marks\n2. Assign Attendance\n3. Logout\n";
                    cout << "Enter your choice: ";
                    cin >> facultyChoice;

                    if (facultyChoice == 1) {
                        string studentID, courseID;
                        double marks;
                        cout << "Enter Student ID: ";
                        cin >> studentID;
                        cout << "Enter Course ID: ";
                        cin >> courseID;
                        cout << "Enter Marks: ";
                        cin >> marks;
                         if(marks>100){
                        
                        auto studentIt = find_if(students.begin(), students.end(),
                                                 [&](const Student& s) { return s.getID() == studentID; });
                        if (studentIt != students.end()) {
                            it->assignMarks(*studentIt, courseID, marks);
                        } else {
                            cout << "Student not found.\n";
                        }
                         }else{
                            cout<<"Inavalid Marks"<<endl;
                            cout<<"Enter Marks:"<<endl;
                            cin>>marks;
                         }
                    
                    } else if (facultyChoice == 2) {
                        string studentID;
                        int days;
                        cout << "Enter Student ID: ";
                        cin >> studentID;
                        cout << "Enter Attendance Percentage: ";
                        cin >> days;

                        auto studentIt = find_if(students.begin(), students.end(),
                                                 [&](const Student& s) { return s.getID() == studentID; });
                        if (studentIt != students.end()) {
                            it->assignAttendance(*studentIt, days);
                        } else {
                            cout << "Student not found.\n";
                        }
                    }
                } while (facultyChoice != 3);
            } else {
                cout << "Invalid credentials.\n";
            }

        } else if (choice == 4) { // Student Login
            string studentID, password;
            cout << "\nEnter Student ID: ";
            cin >> studentID;
            cout << "Enter Password: ";
            cin >> password;

            auto it = find_if(students.begin(), students.end(),
                              [&](const Student& s) { return s.login(studentID, password); });
            if (it != students.end()) {
                cout << "Login successful!\n";
                int studentChoice;
                do {
                    cout << "\n1. View Account\n2. Register for a Course\n3. Logout\n";
                    cout << "Enter your choice: ";
                    cin >> studentChoice;

                    if (studentChoice == 1) {
                        it->viewAccount();

                    } else if (studentChoice == 2) {
                        int semno;
                        cout<<"enter sem no:";
                        cin>>semno;
                        switch (semno) {
            case 1:
                                cout<<"Course Name                   Course  ID"<<endl;
                             cout<<"Engineering Physics             101"<<endl;
                             cout<< "Calculus for Engineers          102"<<endl;
                             cout<<"C Programming                   103"<<endl;
                             cout<<"Analytical Reasoning            104"<<endl;
                             cout<<"Environmental Science           105"<<endl;
                             cout<<"Emerging Technologies           106"<<endl;
                break;
      case 2:
      cout<<"Course Name                   Course  ID"<<endl;
            cout << "Ethics and Human Values             201" << endl;
            cout << "Economics and Management            202" << endl;
            cout << "Data Structures                     203" << endl;
            cout << "Basics of EEE                       204" << endl;
            cout << "Entrepreneurial Mindset             205" << endl;
            cout << "Linear Algebra and DE               206" << endl;
            break;
        case 3:
        cout<<"Course Name                   Course  ID"<<endl;
            cout << "OOPS with C++                       301" << endl;
            cout << "DAA                                 302" << endl;
            cout << "(Minor-1)                           303" << endl; // Added course code 301
            cout << "Discrete Mathematics                304" << endl;
            cout << "Digital Electronics                 305" << endl;
            cout << "Problem Solving Skills              306" << endl;
            break;
        case 4:
        cout<<"Course Name                   Course  ID"<<endl;
            cout << "Web Technology                      401" << endl;
            cout << "Python                              402" << endl;
            cout << "DBMS                                403" << endl;
            cout << "(Minor-2)                           404" << endl;
            cout << "Thinking & Creative Skills          405" << endl;
            cout << "Probability & Statistics            406" << endl;
            break;
        case 5:
        cout<<"Course Name                   Course  ID"<<endl;
            cout << "Computer Networks                   501" << endl;
            cout << "(Minor-3)                           502" << endl;
            cout << "Machine Learning                    503" << endl;
            cout << "Operating Systems                   504" << endl;
            cout << "Automata & Compiler Design          505" << endl;
            cout << "Computer Architecture               506" << endl;
            break;
        case 6:
        cout<<"Course Name                   Course  ID"<<endl;
            cout << "Software Engineering                601" << endl;
            cout << "(Minor-4)                           602" << endl;
            cout << "Core-Elective(1)                    603" << endl;
            cout << "Stream Elective(1)                  604" << endl;
            cout << "App Development (JAVA)              605" << endl;
            cout << "Stream Elective(2)                  606" << endl;
            break;
        case 7:
        cout<<"Course Name                   Course  ID"<<endl;
            cout << "Internship/Project                  701" << endl;
            cout << "(Minor-5)                           702" << endl;
            cout << "Core-Elective(2)                    703" << endl;
            cout << "Stream Elective(3)                  704" << endl;
            cout << "Stream Elective(4)                  705" << endl;
            cout << "Mock Interview Training             706" << endl;
            break;
            case 8:
                cout<<"Major Project"<<endl;
                break;
            default:
                cout << "Invalid semester number.\n";
                break;
        }
                        // string courseID;
                        // cout << "Enter Course ID to register: ";
                        // cin >> courseID;
                        // it->registerCourse(courseID);
                        
                           int numCourses;
    cout << "Enter the number of courses to register for this semester: ";
    cin >> numCourses;

    for (int i = 0; i < numCourses; ++i) {
        string courseID;
        cout << "Enter Course ID for course " << (i + 1) << ": ";
        cin >> courseID;
        it->registerCourse(courseID);
    }

                    } else if (studentChoice != 3) {
                        cout << "Invalid choice. Please try again.\n";
                    }
                } while (studentChoice != 3);
            } else {
                cout << "Invalid credentials.\n";
            }
        }

    } while (choice != 5);

    // Save data to files
    ofstream studentFileOut("students.txt");
    ofstream facultyFileOut("faculties.txt");

    for (const auto& student : students) {
        student.saveToFile(studentFileOut);
    }

    for (const auto& faculty : faculties) {
        faculty.saveToFile(facultyFileOut);
    }

    studentFileOut.close();
    facultyFileOut.close();

    return 0;
}