#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

struct Student
{
    int id;
    string name;
    int age;
    string department;
};

const string FILE_NAME = "students.txt";

// Load students from file
vector<Student> loadStudents()
{
    vector<Student> students;
    ifstream file(FILE_NAME);

    if (!file)
        return students;

    string line;

    while (getline(file, line))
    {
        if (line.empty())
            continue;

        stringstream ss(line);
        Student s;
        string temp;

        getline(ss, temp, ',');
        s.id = stoi(temp);

        getline(ss, s.name, ',');

        getline(ss, temp, ',');
        s.age = stoi(temp);

        getline(ss, s.department);

        students.push_back(s);
    }

    file.close();
    return students;
}

// Save students to file
void saveStudents(vector<Student>& students)
{
    ofstream file(FILE_NAME);

    for (Student s : students)
    {
        file << s.id << ","
             << s.name << ","
             << s.age << ","
             << s.department << endl;
    }

    file.close();
}

// Add Student
void addStudent()
{
    vector<Student> students = loadStudents();

    Student s;

    cout << "\n------ ADD STUDENT ------\n";

    cout << "Enter Student ID: ";
    cin >> s.id;

    cin.ignore();

    // Check duplicate ID
    for (Student st : students)
    {
        if (st.id == s.id)
        {
            cout << "\nStudent ID already exists!\n";
            return;
        }
    }

    cout << "Enter Name: ";
    getline(cin, s.name);

    cout << "Enter Age: ";
    cin >> s.age;

    cin.ignore();

    cout << "Enter Department: ";
    getline(cin, s.department);

    students.push_back(s);

    saveStudents(students);

    cout << "\nStudent Added Successfully!\n";
}
// Display Students
void displayStudents()
{
    vector<Student> students = loadStudents();

    cout << "\n========== STUDENT RECORDS ==========\n";

    if (students.empty())
    {
        cout << "\nNo student records found.\n";
        return;
    }

    cout << "\nID\tName\t\tAge\tDepartment\n";
    cout << "---------------------------------------------\n";

    for (Student s : students)
    {
        cout << s.id << "\t"
             << s.name << "\t\t"
             << s.age << "\t"
             << s.department << endl;
    }
}

// Search Student
void searchStudent()
{
    vector<Student> students = loadStudents();

    int id;
    bool found = false;

    cout << "\nEnter Student ID to Search: ";
    cin >> id;

    for (Student s : students)
    {
        if (s.id == id)
        {
            cout << "\nStudent Found\n";
            cout << "-------------------------\n";
            cout << "ID         : " << s.id << endl;
            cout << "Name       : " << s.name << endl;
            cout << "Age        : " << s.age << endl;
            cout << "Department : " << s.department << endl;

            found = true;
            break;
        }
    }

    if (!found)
    {
        cout << "\nStudent not found.\n";
    }
}
// Update Student
void updateStudent()
{
    vector<Student> students = loadStudents();

    int id;
    bool found = false;

    cout << "\nEnter Student ID to Update: ";
    cin >> id;
    cin.ignore();

    for (auto &s : students)
    {
        if (s.id == id)
        {
            found = true;

            cout << "\nEnter New Name: ";
            getline(cin, s.name);

            cout << "Enter New Age: ";
            cin >> s.age;
            cin.ignore();

            cout << "Enter New Department: ";
            getline(cin, s.department);

            break;
        }
    }

    if (found)
    {
        saveStudents(students);
        cout << "\nStudent Updated Successfully!\n";
    }
    else
    {
        cout << "\nStudent ID not found.\n";
    }
}

// Delete Student
void deleteStudent()
{
    vector<Student> students = loadStudents();

    int id;
    bool found = false;

    cout << "\nEnter Student ID to Delete: ";
    cin >> id;

    vector<Student> updatedStudents;

    for (Student s : students)
    {
        if (s.id == id)
        {
            found = true;
        }
        else
        {
            updatedStudents.push_back(s);
        }
    }

    if (found)
    {
        saveStudents(updatedStudents);
        cout << "\nStudent Deleted Successfully!\n";
    }
    else
    {
        cout << "\nStudent ID not found.\n";
    }
}
// Main Function
int main()
{
    int choice;

    do
    {
        cout << "\n========================================";
        cout << "\n      STUDENT MANAGEMENT SYSTEM";
        cout << "\n========================================";
        cout << "\n1. Add Student";
        cout << "\n2. Display Students";
        cout << "\n3. Search Student";
        cout << "\n4. Update Student";
        cout << "\n5. Delete Student";
        cout << "\n6. Exit";
        cout << "\n----------------------------------------";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch(choice)
        {
            case 1:
                addStudent();
                break;

            case 2:
                displayStudents();
                break;

            case 3:
                searchStudent();
                break;

            case 4:
                updateStudent();
                break;

            case 5:
                deleteStudent();
                break;

            case 6:
                cout << "\nThank you for using Student Management System!\n";
                break;

            default:
                cout << "\nInvalid choice! Please try again.\n";
        }

    } while(choice != 6);

    return 0;
}