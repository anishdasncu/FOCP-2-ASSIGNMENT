
#include <iostream>
#include <vector>
#include <map>
#include <stdexcept>

using namespace std;

class UniversityException : public exception {
protected:
    string message;
public:
    UniversityException(string msg) : message(msg) {}
    const char* what() const noexcept override { return message.c_str(); }
};

class EnrollmentException : public UniversityException {
public:
    EnrollmentException(string msg) : UniversityException("Enrollment Error: " + msg) {}
};

class GradeException : public UniversityException {
public:
    GradeException(string msg) : UniversityException("Grade Error: " + msg) {}
};


class Student {
public:
    string name;
    int roll_number;
    float gpa;
    vector<string> courses;

    Student(string n, int r) : name(n), roll_number(r), gpa(0.0) {}

    void enrollCourse(string course) {
        if (courses.size() >= 5) throw EnrollmentException("Course limit reached!");
        courses.push_back(course);
    }

    void updateGPA(float newGPA) {
        if (newGPA < 0 || newGPA > 10) throw GradeException("Invalid GPA value!");
        gpa = newGPA;
    }

    void displayInfo() const {
        cout << "Name: " << name << " | Roll No: " << roll_number << " | GPA: " << gpa << "\nCourses: ";
        for (const auto& course : courses) cout << course << " ";
        cout << "\n---------------------------------\n";
    }
};


class Professor {
public:
    string name;
    string department;

    Professor(string n, string dept) : name(n), department(dept) {}

    void displayInfo() const {
        cout << "Professor: " << name << " | Department: " << department << "\n";
    }
};


class UniversitySystem {
private:
    map<int, Student> students;
    map<string, Professor> professors;

public:
    void addStudent(Student s) { students[s.roll_number] = s; }
    void addProfessor(Professor p) { professors[p.name] = p; }

    void enrollStudentInCourse(int roll, string course) {
        try {
            if (students.find(roll) == students.end()) throw EnrollmentException("Student not found!");
            students[roll].enrollCourse(course);
        } catch (const UniversityException& e) {
            cerr << "Error: " << e.what() << endl;
        }
    }

    void assignGPA(int roll, float gpa) {
        try {
            if (students.find(roll) == students.end()) throw GradeException("Student not found!");
            students[roll].updateGPA(gpa);
        } catch (const UniversityException& e) {
            cerr << "Error: " << e.what() << endl;
        }
    }

    void displayAllStudents() {
        for (const auto& s : students) s.second.displayInfo();
    }
};


int main() {
    UniversitySystem uni;

    uni.addStudent(Student("Abhishek", 50));
    uni.addStudent(Student("Anish", 80));
    uni.addProfessor(Professor("Einstein", "Physics"));

    int choice, roll;
    string course;
    float gpa;

    while (true) {
        cout << "\n1. Enroll Student in Course\n2. Assign GPA\n3. Show All Students\n4. Exit\nEnter choice: ";
        cin >> choice;
        if (choice == 4) break;

        cout << "Enter Roll Number: ";
        cin >> roll;

        switch (choice) {
            case 1:
                cout << "Enter Course Name: ";
                cin >> course;
                uni.enrollStudentInCourse(roll, course);
                break;
            case 2:
                cout << "Enter GPA: ";
                cin >> gpa;
                uni.assignGPA(roll, gpa);
                break;
            case 3:
                uni.displayAllStudents();
                break;
            default:
                cout << "Invalid choice!\n";
        }
    }

    return 0;
}
