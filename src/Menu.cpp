//
// Created by pedro on 7/16/25.
//
#include "Menu.hpp"
#include "ToDoList.hpp"
#include <iostream>
#include <limits>
#include <filesystem>
#include "InvalidDate.hpp"


using std::cout;
using std::cin;
using std::numeric_limits;
using std::streamsize;
using std::filesystem::remove;
using std::toupper;

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
        // Clears the input stream
        cin.clear();
        // Ignores everything until the next line
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    return userOption;
}

void Menu::ToDoListMap() {
    map<int, string> listNames;
    int index = 1;
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
        listNames.insert({index, fileName});
        index++;
    }
    existingLists = listNames;
}

int Menu::SelectMenu() {
    cout << "===== Existing ToDoLists =====\n";
    // Displays existing lists
    if (existingLists.empty()) {
        cout << "No ToDo lists found.\n";
        return 0;
    }
    for (const auto& pair : existingLists) {
        cout << pair.first << ". " << pair.second << '\n';
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

void Menu::FindToDoList() {
    int listIndex = 0;
    cout << "Enter ToDoList associated number (In Existing ToDoLists Menu): ";
    while (true) {
        // Get iterator if ToDoList is selected
        if (cin >> listIndex) {
            auto found = existingLists.find(listIndex);
            if (found != existingLists.end()) {
                listName = found->second;
                break;
            }
            cout << "Not found try again.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;

        }
        cout << "Invalid input. Please enter a valid option.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}


void Menu::DeleteToDoList() {
    // Path of selected list, corresponding to the variable listName
    string path = "../lists/" + listName + ".json";
    // Using the filesystem function remove to remove the file based on its filepath
    remove(path);
}


int Menu::ToDoListMenu() {
    // Update todolist object so we can execute method's from ToDoList class in following methods of the class
    todolist = ToDoList(listName);

    cout << "===== " << listName << " =====\n";
    // Options from the menu
    cout << "1. Show tasks\n";
    cout << "2. Add task\n";
    // Order ToDoList based on different criteria
    cout << "3. Order by (1 - Alphabetic order | 2 - Due date | 3 - Priority | 4 - Status)\n";
    // Delete tasks
    cout << "4. Remove task\n";
    // Edit task
    cout << "5. Edit task\n";
    // EXIT
    cout << "6. EXIT\n";

    int userOption;
    while (true) {
        cout << "Enter user option (1 | 2 | 3 | 4 | 5 | 6): ";
        if (cin >> userOption && (userOption == SHOW || userOption == ADD || userOption == ORDER || userOption == REMOVE
                                    || userOption == EDIT || userOption == TD_EXIT)) {
            break;
        }
        cout << "Invalid input. Please enter a valid option.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return userOption;
}


void Menu::ShowToDoList() {
    todolist.outputFile();
}


string Menu::ToUpper(string &str) {
    for (auto& chr: str) {
        chr = toupper(chr);
    }
    return str;
}


string Menu::TaskNameInput() {
    // Name field
    string name;
    // Flag
    while (true) {
        cout << "Enter the task name: \n";
        if (cin >> name) {
            break;
        }
        cout << "Invalid input. Please enter a valid option.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return name;
}


Date Menu::DateInput() {
    int day, month, year;

    while (true) {
        // Outputs to the user
        cout << "Enter the day (1 - 31): ";
        // If the input stream is not correct output error message and clear input stream, restarting the loop
        if (!(cin >> day)) {
            cout << "Invalid input for day. Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        cout << "Enter the month (1 - 12): ";
        if (!(cin >> month)) {
            cout << "Invalid input for month. Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        cout << "Enter the year (>= 1): ";
        if (!(cin >> year)) {
            cout << "Invalid input for year. Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        // Try to create a valid date
        try {
            Date testDate(day, month, year);
            return testDate;
        } catch (const InvalidDate& e) {
            cout << "Caught exception: " << e.what() << '\n';
            cout << "Try again with a valid date.\n";
        }

        // Clear input state and ignore rest of line for clean retry
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}


string Menu::TaskPriorityInput() {
    // Name field
    string priority;
    // Flag
    while (true) {
        cout << "Enter the task priority (HIGH | NORMAL | LOW - case insensitive): \n";
        if (cin >> priority && (ToUpper(priority) == "HIGH" || ToUpper(priority) == "NORMAL" ||
            ToUpper(priority) == "LOW")) {
            break;
        }
        cout << "Invalid input. Please enter a valid option.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return priority;
}


string Menu::TaskStatusInput() {
    // Name field
    string status;
    // Flag
    while (true) {
        cout << "Enter the task priority (IN PROGRESS | TODO - case insensitive): \n";
        if (cin >> status && (ToUpper(status) == "IN PROGRESS" || ToUpper(status) == "TODO")) {
            break;
            }
        cout << "Invalid input. Please enter a valid option.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return status;
}


void Menu::AddTask() {
    // Get task name
    string name = TaskNameInput();
    // Get task date
    Date date = DateInput();
    // Get task priority
    string priority = TaskPriorityInput();
    // Get task status
    string status = TaskStatusInput();
    // Create new task object
    Task task(name, date, priority, status);
    currentTask = task;
    // Add task to todolist
    todolist.addTask(currentTask);
    todolist.saveFile();
}


