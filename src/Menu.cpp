//
// Created by pedro on 7/16/25.
//
#include "Menu.hpp"
#include <iostream>
#include <limits>
#include <filesystem>

using std::cout;
using std::cin;
using std::set;
using std::string;
using std::numeric_limits;
using std::streamsize;

Menu::Menu() {}


int Menu::IntroMenu() {
    cout << "===== ToDoList INTRO MENU =====\n";
    cout << "1. Check existing ToDo Lists\n";
    cout << "2. EXIT\n";

    int userOption;
    while (true) {
        cout << "Enter user option (1 | 2): ";
        if (cin >> userOption && (userOption == CHECK|| userOption == INTRO_EXIT)) {
            break;
        }
        cout << "Invalid input. Please enter a valid option\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    return userOption;
}

set<string> Menu::ToDoListVector() {
    set<string> listNames;
    string path = "../lists/";
    // Iterates over paths in the /list directory
    for (const auto & entry : std::filesystem::directory_iterator(path)) {
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

int Menu::SelectMenu() {
    cout << "===== Existing ToDoLists =====\n";
    // Displays existing lists
    if (existingLists.empty()) {
        cout << "No ToDo lists found.\n";
        return 0;
    }
    int index = 1;
    for (const auto& name : existingLists) {
        cout << index++ << ". " << name << '\n';
    }
    cout << "===== ToDoLists MENU =====\n";
    cout << "1. Select ToDoList\n";
    cout << "2. Delete ToDoList\n";
    cout << "3. EXIT\n";

    int userOption;
    while (true) {
        cout << "Enter user option (1 | 2 | 3): ";
        if (cin >> userOption && (userOption == SELECT || userOption == DELETE || userOption == SELECT_EXIT)) {
            break;
        }
        cout << "Invalid input. Please enter a valid option.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return userOption;
}
