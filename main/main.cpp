#include <iostream>
#include <limits>
#include <string>
#include <filesystem>
#include <set>
using namespace std;


enum IntroMenu {
    CHECK = 1,
    EXIT
};

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

// Displays the existing ToDoList names
void SelectToDoListMENU(const set<string>& existingLists) {
    if (existingLists.empty()) {
        cout << "No ToDo lists found." << endl;
        return;
    }

    cout << "===== ToDoLists MENU =====" << endl;
    int index = 1;
    for (const auto& name : existingLists) {
        cout << index++ << ". " << name << endl;
    }
}

// Displays intro menu and returns the selected option
int IntroMenuHandler() {
    cout << "===== ToDoList INTRO MENU =====" << endl;
    cout << "1. Check existing ToDo Lists" << endl;
    cout << "2. EXIT" << endl;

    int userOption;
    while (true) {
        cout << "Enter user option (1 | 2): ";
        if (cin >> userOption && (userOption == CHECK || userOption == EXIT)) {
            break;
        }
        cout << "Invalid input. Please enter a valid option." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    return userOption;
}


int main() {
    // Get user selection
    int userIntroMenu = IntroMenuHandler();
    // Option selected
    if (userIntroMenu == CHECK) {
        // Set with lists names
        set<string> lists = ToDoListVector();
        SelectToDoListMENU(lists);
    }
    return 0;
}