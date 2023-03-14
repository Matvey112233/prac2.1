#include <iostream>
#include <string>

using namespace std;

const int MAX_STUDENTS = 50;

struct Student {
    string name;
    char gender;
    int group_number;
    int list_number;
    int grades[8];
};

void create_student(Student* students, int& count) {
    if (count >= MAX_STUDENTS) {
        cout << "Maximum number of students reached." << endl;
        return;
    }
    Student new_student;
    cout << "Enter student name: ";
    getline(cin, new_student.name);
    cout << "Enter student gender (M/W): ";
    cin >> new_student.gender;
    cout << "Enter student group number: ";
    cin >> new_student.group_number;
    cout << "Enter student list number: ";
    cin >> new_student.list_number;
    cout << "Enter student grades for 3 exams and 5 differentiated credits: ";
    for (int i = 0; i < 8; i++) {
        cin >> new_student.grades[i];
    }
    students[count] = new_student;
    count++;
}

void edit_student(Student* students, int count) {
    cout << "Enter the index of the student you want to edit (0-" << count - 1 << "): ";
    int index;
    cin >> index;
    if (index < 0 || index >= count) {
        cout << "Invalid index." << endl;
        return;
    }
    cout << "Enter new student name: ";
    cin.ignore();
    getline(cin, students[index].name);
    cout << "Enter new student gender (M/W): ";
    cin >> students[index].gender;
    cout << "Enter new student group number: ";
    cin >> students[index].group_number;
    cout << "Enter new student list number: ";
    cin >> students[index].list_number;
    cout << "Enter new student grades for 3 exams and 5 differentiated credits: ";
    for (int i = 0; i < 8; i++) {
        cin >> students[index].grades[i];
    }
}

void print_students(Student* students, int count) {
    for (int i = 0; i < count; i++) {
        cout << "Student #" << i + 1 << endl;
        cout << "Name: " << students[i].name << endl;
        cout << "Gender: " << students[i].gender << endl;
        cout << "Group number: " << students[i].group_number << endl;
        cout << "List number: " << students[i].list_number << endl;
        cout << "Grades:";
        for (int j = 0; j < 8; j++) {
            cout << " " << students[i].grades[j];
        }
        cout << endl;
    }
}

void print_students_by_group(Student students[], int numStudents, int groupNumber) {
    cout << "Students in group " << groupNumber << ":" << endl;
    for (int i = 0; i < numStudents; i++) {
        if (students[i].group_number == groupNumber) {
            cout << "Student #" << i + 1 << ":" << endl;
            cout << "Name: " << students[i].name << endl;
            cout << "Gender: " << students[i].gender << endl;
            cout << "Group number: " << students[i].group_number << endl;
            cout << "List number: " << students[i].list_number << endl;
            cout << "Grades:";
            for (int j = 0; j < 8; j++) {
                cout << " " << students[i].grades[j];
            }
            cout << endl;
        }
    }
}

float get_average_score(const Student& student) {
    float sum = 0;
    for (int i = 0; i < 8; i++) {
        sum += student.grades[i];
    }
    return sum / 8;
}

void print_average_scores(Student* students, int count) {
    for (int i = 0; i < count; i++) {
        for (int j = i + 1; j < count; j++) {
            float score1 = get_average_score(students[i]);
            float score2 = get_average_score(students[j]);
            if (score1 < score2) {
                std::swap(students[i], students[j]);
            }
        }
    }
    for (int i = 0; i < count; i++) {
        float score = get_average_score(students[i]);
        cout << students[i].name << " - " << score << endl;
    }
}

void print_gender_count(const Student students[], int count) {
    int man_count = 0;
    int women_count = 0;
    for (int i = 0; i < count; i++) {
        if (students[i].gender == 'M') {
            man_count++;
        }
        else if (students[i].gender == 'W') {
            women_count++;
        }
    }
    cout << "Man students: " << man_count << endl;
    cout << "Women students: " << women_count << endl;
}

void print_students_without_scholarship(const Student* students, int count) {
    for (int i = 0; i < count; i++) {
        bool has_scholarship = true;
        bool has_low_grade = false;
        for (int j = 0; j < 8; j++) {
            if (students[i].grades[j] < 4) {
                has_scholarship = false;
                if (students[i].grades[j] == 3) {
                    has_low_grade = true;
                }
            }
        }
        if (has_scholarship || !has_low_grade) {
            continue;
        }
        cout << students[i].name << "(" << students[i].group_number << ")" << ", grades: ";
        for (int j = 0; j < 8; j++) {
            cout << students[i].grades[j] << " ";
        }
        cout << endl;
    }
}

void print_students_with_good_and_excellent_grades(const Student* students, int count) {
    for (int i = 0; i < count; i++) {
        bool has_bad_grade = false;
        bool has_excellent_grade = false;
        bool has_grade_3 = false;
        for (int j = 0; j < 8; j++) {
            if (students[i].grades[j] < 4) {
                has_bad_grade = true;
            }
            else if (students[i].grades[j] == 4) {
                has_excellent_grade = true;
            }
            else if (students[i].grades[j] == 3) {
                has_grade_3 = true;
            }
        }
        if (has_bad_grade || !has_excellent_grade || (!has_grade_3 && !has_excellent_grade)) {
            continue;
        }
        bool all_5_grades = true;
        for (int j = 0; j < 8; j++) {
            if (students[i].grades[j] != 5) {
                all_5_grades = false;
                break;
            }
        }
        if (all_5_grades) {
            continue;
        }
        cout << students[i].name << "(" << students[i].group_number << ")" << ", grades: ";
        for (int j = 0; j < 8; j++) {
            cout << students[i].grades[j] << " ";
        }
        cout << endl;
    }
}

void print_students_with_excellent_grades(const Student* students, int count) {
    for (int i = 0; i < count; i++) {
        bool has_bad_grade = false;
        for (int j = 0; j < 8; j++) {
            if (students[i].grades[j] != 5) {
                has_bad_grade = true;
                break;
            }
        }
        if (has_bad_grade) {
            continue;
        }
        cout << students[i].name << "(" << students[i].group_number << ")" << ", grades: ";
        for (int j = 0; j < 8; j++) {
            cout << students[i].grades[j] << " ";
        }
        cout << endl;
    }
}

void print_students_by_list_number(Student students[], int numStudents, int listNumber) {
    cout << "Students in list " << listNumber << ":" << endl;
    for (int i = 0; i < numStudents; i++) {
        if (students[i].list_number == listNumber) {
            cout << "Student #" << i + 1 << ":" << endl;
            cout << "Name: " << students[i].name << endl;
            cout << "Gender: " << students[i].gender << endl;
            cout << "Group number: " << students[i].group_number << endl;
            cout << "List number: " << students[i].list_number << endl;
            cout << "Grades:";
            for (int j = 0; j < 8; j++) {
                cout << " " << students[i].grades[j];
            }
            cout << endl;
        }
    }
}

int main() {
    Student students[MAX_STUDENTS];
    int count = 0;
    int groupNumber;
    int listNumber;
    while (true) {
        int task;
        cout << "Choose an operation:" << endl;
        cout << "1. Create new student " << endl;
        cout << "2. Edit student information" << endl;
        cout << "3. Show information" << endl;
        cout << "4. Information of group" << endl;
        cout << "5. Top student" << endl;
        cout << "6. Man and women students" << endl;
        cout << "7. Students without scholarship; good and excellent; only excellent" << endl;
        cout << "8. Students by list number" << endl;
        cout << "0. Exit" << endl;
        cin >> task;
        cin.ignore();
        switch (task) {
        case 1:
            create_student(students, count);
            break;
        case 2:
            edit_student(students, count);
            break;
        case 3:
            print_students(students, count);
            break;
        case 4:
            cout << "Enter group number: ";
            cin >> groupNumber;
            print_students_by_group(students, count, groupNumber);
            break;
        case 5:
            cout << "Top students:" << endl;
            print_average_scores(students, count);
            break;
        case 6:
            print_gender_count(students, count);
            break;
        case 7:
            cout << "Without scholarship:" << endl;
            print_students_without_scholarship(students, count);
            cout << endl;
            cout << "Good and excellent:" << endl;
            print_students_with_good_and_excellent_grades(students, count);
            cout << endl;
            cout << "Only excellent:" << endl;
            print_students_with_excellent_grades(students, count);
            cout << endl;
            break;
        case 8:
            cout << "Enter list number: ";
            cin >> listNumber;
            print_students_by_list_number(students, count, listNumber);
            break;
        case 0: {exit(0);};
              break;
        default:
            break;
        }
    }
    return 0;
}
