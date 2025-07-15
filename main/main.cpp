//
// Created by pedro on 7/15/25.
//
#include <iostream>
#include <limits>
#include <string>
#include <filesystem>
#include <set>
using namespace std;

// Enums for different MENUS
enum IntroMenu{CHECK = 1, INTRO_EXIT = 2};
enum SelectMenu {SELECT = 1, DELETE = 2, SELECT_EXIT = 3 };

// Function declaration
int IntroMenu();
set<string> ToDoListVector();
void IntroMenuWrapper();
int SelectMenu(const set<string>& existingLists);
void SelectMenuWrapper();


// Function implementation
// Displays intro menu and returns the selected option
int IntroMenu() {
    cout << "===== ToDoList INTRO MENU =====" << endl;
    cout << "1. Check existing ToDo Lists" << endl;
    cout << "2. EXIT" << endl;

    int userOption;
    while (true) {
        cout << "Enter user option (1 | 2): ";
        if (cin >> userOption && (userOption == CHECK|| userOption == INTRO_EXIT)) {
            break;
        }
        cout << "Invalid input. Please enter a valid option." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    return userOption;
}


set<string> ToDoListVector() {
    set<string> listNames;
    string path = "../lists/";
    // Iterates over paths in the /list directory
    for (const auto & entry : filesystem::directory_iterator(path)) {
        string fileName = entry.path().generic_string();
        // First index to trim fileName
        size_t start = fileName.find_last_of('/');
        // Last index to trim fileName
        size_t end = fileName.find_last_of('.');
        // Get substring based on previous indexes
        fileName = fileName.substr(start + 1, fileName.length() - end);
        // Output fileName
        listNames.insert(fileName);
    }
    return listNames;
}

void IntroMenuWrapper() {
    // Get user selection
    int userIntroMenu = IntroMenu();
    // Option selected
    if (userIntroMenu == CHECK) {
        // Set with lists names
        set<string> lists = ToDoListVector();
        // Display existing lists
        SelectMenu(lists);
    }
}


// Displays the existing ToDoList names
int SelectMenu(const set<string>& existingLists) {
    cout << "===== Existing ToDoLists =====" << endl;
    // Displays existing lists
    if (existingLists.empty()) {
        cout << "No ToDo lists found." << endl;
        return 0;
    }
    int index = 1;
    for (const auto& name : existingLists) {
        cout << index++ << ". " << name << endl;
    }
    cout << "===== ToDoLists MENU =====" << endl;
    cout << "1. Select ToDoList" << endl;
    cout << "2. Delete ToDoList" << endl;
    cout << "3. EXIT" << endl;

    int userOption;
    while (true) {
        cout << "Enter user option (1 | 2 | 3): ";
        if (cin >> userOption && (userOption == SELECT || userOption == DELETE || userOption == SELECT_EXIT)) {
            break;
        }
        cout << "Invalid input. Please enter a valid option." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return userOption;
}

void SelectMenuWrapper() {
}


int main() {
    IntroMenuWrapper();
    return 0;
}