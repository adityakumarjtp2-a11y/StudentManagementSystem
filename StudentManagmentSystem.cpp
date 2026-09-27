#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

struct Student {
    int id;
    string name;
    int age;
    string course;
    float marks;
};

void saveStudents(const vector<Student>& students) {
    ofstream file("students.txt");

    for (const Student& s : students) {
        file << s.id << "|" << s.name << "|" << s.age << "|"
             << s.course << "|" << s.marks << endl;
    }

    file.close();
}

void loadStudents(vector<Student>& students) {
    ifstream file("students.txt");

    int id;
    string name;
    int age;
    string course;
    float marks;
    char separator;

    while (file >> id) {
        file.get(separator);
        getline(file, name, '|');

        file >> age;
        file.get(separator);

        getline(file, course, '|');

        file >> marks;
        file.ignore();

        students.push_back({id, name, age, course, marks});
    }

    file.close();
}

int main() {
    vector<Student> students;
    int choice;

    loadStudents(students);

    while (true) {
        cout << "\n===== Student Management System =====" << endl;
        cout << "1. Add Student" << endl;
        cout << "2. View Students" << endl;
        cout << "3. Search Student" << endl;
        cout << "4. Update Student" << endl;
        cout << "5. Delete Student" << endl;
        cout << "6. Exit" << endl;

        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            Student s;

            cout << "Enter student ID: ";
            cin >> s.id;
            cin.ignore();

            cout << "Enter student name: ";
            getline(cin, s.name);

            cout << "Enter student age: ";
            cin >> s.age;
            cin.ignore();

            cout << "Enter student course: ";
            getline(cin, s.course);

            cout << "Enter student marks: ";
            cin >> s.marks;

            students.push_back(s);
            saveStudents(students);

            cout << "Student added successfully!" << endl;
        }

        else if (choice == 2) {
            if (students.empty()) {
                cout << "No students added yet." << endl;
            }
            else {
                cout << "\n===== Student List =====" << endl;

                for (int i = 0; i < students.size(); i++) {
                    cout << "Student " << i + 1 << endl;
                    cout << "ID: " << students[i].id << endl;
                    cout << "Name: " << students[i].name << endl;
                    cout << "Age: " << students[i].age << endl;
                    cout << "Course: " << students[i].course << endl;
                    cout << "Marks: " << students[i].marks << endl;

                    if (students[i].marks >= 40) {
                        cout << "Result: Pass" << endl;
                    }
                    else {
                        cout << "Result: Fail" << endl;
                    }

                    if (students[i].marks >= 80) {
                        cout << "Grade: A" << endl;
                    }
                    else if (students[i].marks >= 60) {
                        cout << "Grade: B" << endl;
                    }
                    else if (students[i].marks >= 40) {
                        cout << "Grade: C" << endl;
                    }
                    else {
                        cout << "Grade: F" << endl;
                    }

                    cout << "-------------------" << endl;
                }
            }
        }

        else if (choice == 3) {
            string searchName;
            bool found = false;

            cout << "Enter student name to search: ";
            getline(cin, searchName);

            for (const Student& s : students) {
                if (s.name == searchName) {
                    cout << "\nStudent Found!" << endl;
                    cout << "ID: " << s.id << endl;
                    cout << "Name: " << s.name << endl;
                    cout << "Age: " << s.age << endl;
                    cout << "Course: " << s.course << endl;
                    cout << "Marks: " << s.marks << endl;

                    if (s.marks >= 40) {
                        cout << "Result: Pass" << endl;
                    }
                    else {
                        cout << "Result: Fail" << endl;
                    }

                    found = true;
                }
            }

            if (!found) {
                cout << "Student not found." << endl;
            }
        }

        else if (choice == 4) {
            int updateId;
            bool found = false;

            cout << "Enter student ID to update: ";
            cin >> updateId;
            cin.ignore();

            for (Student& s : students) {
                if (s.id == updateId) {
                    cout << "Enter new name: ";
                    getline(cin, s.name);

                    cout << "Enter new age: ";
                    cin >> s.age;
                    cin.ignore();

                    cout << "Enter new course: ";
                    getline(cin, s.course);

                    cout << "Enter new marks: ";
                    cin >> s.marks;
                    cin.ignore();

                    saveStudents(students);

                    cout << "Student updated successfully!" << endl;
                    found = true;
                    break;
                }
            }

            if (!found) {
                cout << "Student not found." << endl;
            }
        }

        else if (choice == 5) {
            int deleteId;
            bool found = false;

            cout << "Enter student ID to delete: ";
            cin >> deleteId;
            cin.ignore();

            for (int i = 0; i < students.size(); i++) {
                if (students[i].id == deleteId) {
                    students.erase(students.begin() + i);
                    saveStudents(students);

                    cout << "Student deleted successfully!" << endl;
                    found = true;
                    break;
                }
            }

            if (!found) {
                cout << "Student not found." << endl;
            }
        }

        else if (choice == 6) {
            cout << "Thank you!" << endl;
            break;
        }

        else {
            cout << "Invalid choice!" << endl;
        }
    }

    return 0;
}