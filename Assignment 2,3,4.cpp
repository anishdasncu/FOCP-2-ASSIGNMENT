
#include <iostream>
#include <string>

using namespace std;


class Person {
protected:
    string name;
    int age;
public:
    Person(string n, int a) : name(n), age(a) {}
    virtual void displayDetails() {
        cout << "Name: " << name << ", Age: " << age << endl;
    }
};


class Student : public Person {
protected:
    int studentID;
public:
    Student(string n, int a, int id) : Person(n, a), studentID(id) {}
    virtual void displayDetails() override {
        cout << "Student ID: " << studentID << ", ";
        Person::displayDetails();
    }
};


class UndergraduateStudent : public Student {
    string major, minor;
    string expectedGraduationDate;
public:
    UndergraduateStudent(string n, int a, int id, string mj, string mn, string grad)
        : Student(n, a, id), major(mj), minor(mn), expectedGraduationDate(grad) {}
    void displayDetails() override {
        Student::displayDetails();
        cout << "Major: " << major << ", Minor: " << minor
             << ", Graduation: " << expectedGraduationDate << endl;
    }
};

class GraduateStudent : public Student {
    string researchTopic, advisor, thesisTitle;
public:
    GraduateStudent(string n, int a, int id, string rt, string adv, string thesis)
        : Student(n, a, id), researchTopic(rt), advisor(adv), thesisTitle(thesis) {}
    void displayDetails() override {
        Student::displayDetails();
        cout << "Research Topic: " << researchTopic << ", Advisor: " << advisor
             << ", Thesis: " << thesisTitle << endl;
    }
};

// Base Class: Professor
class Professor : public Person {
protected:
    int yearsOfExperience;
public:
    Professor(string n, int a, int exp) : Person(n, a), yearsOfExperience(exp) {}
    virtual double calculatePayment() {
        return 10 + (yearsOfExperience * 25); 
}
};


class AssistantProfessor : public Professor {
public:
    AssistantProfessor(string n, int a, int exp) : Professor(n, a, exp) {}
    double calculatePayment() override {
        return Professor::calculatePayment() + 10; 
    }
};

class AssociateProfessor : public Professor {
public:
    AssociateProfessor(string n, int a, int exp) : Professor(n, a, exp) {}
    double calculatePayment() override {
        return Professor::calculatePayment() + 20; 
    }
};

class FullProfessor : public Professor {
public:
    FullProfessor(string n, int a, int exp) : Professor(n, a, exp) {}
    double calculatePayment() override {
        return Professor::calculatePayment() + 30;
    }

};

class Department {
    string deptName;
    Professor* professors[5]; 
    int profCount;
public:
    Department(string name) : deptName(name), profCount(0) {}
    void addProfessor(Professor* prof) {
        if (profCount < 5) professors[profCount++] = prof;
    }
    void displayProfessors() {
        cout << "Department: " << deptName << endl;
        for (int i = 0; i < profCount; i++)
            professors[i]->displayDetails();
    }
};


class Course {
    string courseName;
    Professor* instructor;
public:
    Course(string name, Professor* prof) : courseName(name), instructor(prof) {}
    void displayCourse() {
        cout << "Course: " << courseName << endl;
        instructor->displayDetails();
    }
};


class University {
    Department* departments[3]; 
    int deptCount;
public:
    University() : deptCount(0) {}
    void addDepartment(Department* dept) {
        if (deptCount < 3) departments[deptCount++] = dept;
    }
    void displayUniversity() {
        cout << "University Details"<<endl;
        for (int i = 0; i < deptCount; i++)
            departments[i]->displayProfessors();
    }
};


int main() {
   
    AssistantProfessor ap("Anish", 19, 5);
    AssociateProfessor asp("Dhruv", 20, 10);
    FullProfessor fp("Abhishek",18,15);

    
    Department csDept("Computer Science");
    csDept.addProfessor(&ap);
    csDept.addProfessor(&asp);
    csDept.addProfessor(&fp);

    
    University uni;
    uni.addDepartment(&csDept);

    
    uni.displayUniversity();

    
    Course pythonCourse("Data Science", &fp);
    pythonCourse.displayCourse();

    return 0;
}





