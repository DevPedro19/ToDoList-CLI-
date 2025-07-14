#include <iostream>
#include <limits>
#include <string>
#include <filesystem>
using namespace std;


enum IntroMenu {
    CHECK = 1,
    EXIT
};

void ToDoListDisplay() {
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
        std::cout << fileName << std::endl;
    }
}

int IntroMenuHandler(){
    // Displays message
    cout << "=====ToDoList INTRO MENU=====" << endl;
    cout << "1. Check existing ToDo Lists" << endl;
    cout << "2. EXIT" << endl;


    // Gets validated user input
    cout << "Enter user option ( 1 | 2 ): ";
    int userOption;
    while (true) {
        // User userOption
        // Check if the value is valid
        if (cin >> userOption && (userOption == CHECK || userOption == EXIT)) {
            break;
        }
        cout << "Invalid input. Please enter a valid option." << endl;
        // Clears input value
        cin.clear();
        // Cleanup of the input buffer (ignores everything until the newline delimiter)
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }


    // Check user option
     if (userOption == CHECK) {
         std::cout << "=====LISTS MENU=====" << std::endl;
         ToDoListDisplay();
    }
    return 0;
}

// Select ToDoList MENU



int main() {
    // Intro Menu
    IntroMenuHandler();

}