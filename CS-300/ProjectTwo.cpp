// CS 300 Project Two - ABCU Advising Assistance Program
// Monica Kim
// Stores course information in a binary search tree.
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cctype>
using namespace std;

struct Course {
    string courseNumber;
    string courseName;
    vector<string> prerequisites;
};

string trim(string text) {
    size_t first = text.find_first_not_of(" \t\r\n");
    if (first == string::npos) return "";
    size_t last = text.find_last_not_of(" \t\r\n");
    return text.substr(first, last - first + 1);
}

string upperCase(string text) {
    for (int i = 0; i < (int)text.length(); i++) {
        text[i] = toupper((unsigned char)text[i]);
    }
    return text;
}

class BinarySearchTree {
private:
    struct Node {
        Course course;
        Node* left;
        Node* right;
    };
    Node* root;
    int count;

    Node* insertNode(Node* node, Course course, bool& inserted) {
        if (node == nullptr) {
            Node* newNode = new Node;
            newNode->course = course;
            newNode->left = nullptr;
            newNode->right = nullptr;
            inserted = true;
            return newNode;
        }
        if (course.courseNumber < node->course.courseNumber) {
            node->left = insertNode(node->left, course, inserted);
        }
        else if (course.courseNumber > node->course.courseNumber) {
            node->right = insertNode(node->right, course, inserted);
        }
        return node;
    }

    void printInOrder(Node* node) {
        if (node == nullptr) return;
        printInOrder(node->left);
        cout << node->course.courseNumber << ", " << node->course.courseName << endl;
        printInOrder(node->right);
    }

    void deleteNodes(Node* node) {
        if (node == nullptr) return;
        deleteNodes(node->left);
        deleteNodes(node->right);
        delete node;
    }

public:
    BinarySearchTree() {
        root = nullptr;
        count = 0;
    }
    ~BinarySearchTree() { deleteNodes(root); }

    bool insert(Course course) {
        bool inserted = false;
        root = insertNode(root, course, inserted);
        if (inserted) count++;
        return inserted;
    }

    Course* search(string courseNumber) {
        Node* current = root;
        while (current != nullptr) {
            if (courseNumber == current->course.courseNumber)
                return &current->course;
            if (courseNumber < current->course.courseNumber)
                current = current->left;
            else
                current = current->right;
        }
        return nullptr;
    }

    void printAll() { printInOrder(root); }
    int size() { return count; }
};

// Return a new tree only if the entire file is valid.
BinarySearchTree* loadCourses(string fileName) {
    ifstream file(fileName);
    if (!file.is_open()) {
        cout << "Error: Could not open file: " << fileName << endl;
        return nullptr;
    }

    BinarySearchTree* tree = new BinarySearchTree;
    vector<Course> records;
    string line;
    int lineNumber = 0;

    while (getline(file, line)) {
        lineNumber++;
        if (trim(line) == "") continue;

        stringstream row(line);
        vector<string> parts;
        string value;
        while (getline(row, value, ',')) {
            parts.push_back(trim(value));
        }
        if (parts.size() < 2 || parts[0] == "" || parts[1] == "") {
            cout << "Error: Invalid course data on line " << lineNumber << endl;
            delete tree;
            return nullptr;
        }

        Course course;
        course.courseNumber = upperCase(parts[0]);
        course.courseName = parts[1];
        for (int i = 2; i < (int)parts.size(); i++) {
            if (parts[i] != "") course.prerequisites.push_back(upperCase(parts[i]));
        }
        if (!tree->insert(course)) {
            cout << "Error: Duplicate course " << course.courseNumber << endl;
            delete tree;
            return nullptr;
        }
        records.push_back(course);
    }
    file.close();

    if (tree->size() == 0) {
        cout << "Error: No courses found in the file." << endl;
        delete tree;
        return nullptr;
    }
    for (int i = 0; i < (int)records.size(); i++) {
        for (int j = 0; j < (int)records[i].prerequisites.size(); j++) {
            string needed = records[i].prerequisites[j];
            if (tree->search(needed) == nullptr) {
                cout << "Error: Prerequisite " << needed << " was not found." << endl;
                delete tree;
                return nullptr;
            }
        }
    }
    return tree;
}

void printCourse(BinarySearchTree* tree, string courseNumber) {
    Course* course = tree->search(upperCase(trim(courseNumber)));
    if (course == nullptr) {
        cout << "Course not found. Please enter a valid course number." << endl;
        return;
    }
    cout << course->courseNumber << ", " << course->courseName << endl;
    if (course->prerequisites.size() == 0) {
        cout << "Prerequisites: None" << endl;
    }
    else {
        cout << "Prerequisites: ";
        for (int i = 0; i < (int)course->prerequisites.size(); i++) {
            if (i > 0) cout << ", ";
            Course* prereq = tree->search(course->prerequisites[i]);
            if (prereq != nullptr) {
                cout << prereq->courseNumber << " (" << prereq->courseName << ")";
            }
        }
        cout << endl;
    }
}

int main() {
    BinarySearchTree* courses = nullptr;
    string choice;
    cout << "Welcome to the course planner." << endl;

    while (choice != "9") {
        cout << "\n1. Load Data Structure.\n";
        cout << "2. Print Course List.\n";
        cout << "3. Print Course.\n";
        cout << "9. Exit\n\n";
        cout << "What would you like to do? ";
        if (!getline(cin, choice)) break;
        choice = trim(choice);

        if (choice == "1") {
            string fileName;
            cout << "Enter the course data file name: ";
            if (!getline(cin, fileName)) break;
            BinarySearchTree* newCourses = loadCourses(trim(fileName));
            if (newCourses != nullptr) {
                delete courses;
                courses = newCourses;
                cout << courses->size() << " courses loaded successfully." << endl;
            }
        }
        else if (choice == "2") {
            if (courses == nullptr) cout << "Please load course data first (option 1)." << endl;
            else {
                cout << "Here is a sample schedule:\n" << endl;
                courses->printAll();
            }
        }
        else if (choice == "3") {
            if (courses == nullptr) cout << "Please load course data first (option 1)." << endl;
            else {
                string courseNumber;
                cout << "What course do you want to know about? ";
                if (!getline(cin, courseNumber)) break;
                printCourse(courses, courseNumber);
            }
        }
        else if (choice == "9") {
            cout << "Thank you for using the course planner!" << endl;
        }
        else {
            cout << choice << " is not a valid option. Please choose 1, 2, 3, or 9." << endl;
        }
    }
    delete courses;
    return 0;
}
