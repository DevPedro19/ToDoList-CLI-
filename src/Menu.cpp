//
// Created by pedro on 7/16/25.
//
#include "Menu.hpp"
#include "ToDoList.hpp"
#include <iostream>
#include <limits>
#include <filesystem>
#include <fstream>
#include "InvalidDate.hpp"


using std::cout;
using std::cin;
using std::numeric_limits;
using std::streamsize;
using std::filesystem::remove;
using std::toupper;
using std::ofstream;
using std::filesystem::exists;
using std::cout;

Menu::Menu() {}

// Intro Menu: Check existing lists or fully exit the program
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


// Iterates over the files in the lists folder and then it maps them out to a map so its easier to access for the user
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
        fileName = fileName.substr(start + 1, end - start - 1);
        // Output fileName
        listNames.insert({index, fileName});
        index++;
    }
    existingLists = listNames;
}


// SelectMenu: Allows the user to perform operations in the existing lists (.csv files) and handles case when there are no lists
int Menu::SelectMenu() {
    cout << "===== Existing ToDoLists =====\n";
    // Displays existing lists
    if (existingLists.empty()) {
        cout << "No ToDo lists found.\n";
        cout << "As no list was found we have to add at least one.\n";
        // If no list was found we have to add one so we call the function that adds the new ToDoList
        AddNewToDoList();
    }
    for (const auto& pair : existingLists) {
        cout << pair.first << ". " << pair.second << '\n';
    }
    cout << "===== ToDoLists MENU =====\n";
    cout << "1. Select ToDoList\n";
    cout << "2. Delete ToDoList\n";
    cout << "3. Add ToDoList\n";
    cout << "4. EXIT\n";

    int userOption;
    while (true) {
        cout << "Enter user option (1 | 2 | 3 | 4): ";
        if (cin >> userOption && (userOption == SELECT || userOption == DELETE || userOption == ADD_LIST || userOption == SELECT_EXIT)) {
            break;
        }
        cout << "Invalid input. Please enter a valid option.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return userOption;
}


// Finder of the list by user index
void Menu::FindToDoList() {
    int user = 0;
    cout << "Enter ToDoList associated number (In Existing ToDoLists Menu): ";
    while (true) {
        // Get iterator if ToDoList is selected
        if (cin >> user) {
            auto found = existingLists.find(user);
            if (found != existingLists.end()) {
                currentListIndex = found->first;
                currentListName = found->second;
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


// Delete ToDoList from the filesystem and also from the vector
void Menu::DeleteToDoList() {
    // Using the filesystem function remove to remove the file based on its filepath
    remove("../lists/" + currentListName + ".csv");
    // Remove from existingLists
    existingLists.erase(currentListIndex);
}


// Finder by name
bool Menu::FoundName(string& name) {
    bool found = false;
    for (auto& pair: existingLists) {
        if (pair.second == name) {
            found = true;
        }
    }
    return found;
}


// Adds new list to the files and to the existingLists vector
void Menu::AddNewToDoList() {
    // Name field
    string name;
    while (true) {
        cout << "Enter the ToDoList name: ";
        // If the string is valid and the file doesn't exist
        /* When using getline we have to make sure that the input stream is clear
         * because cin leaves any newline or space behind so we have to skip it so we use cin.ignore*/
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (getline(cin, name) && !FoundName(name)) {
            // Create a new file
            ofstream out("../lists/" + name + ".csv");
            // Add it to existing lists

            // If the list is empty we create a new entry
            if (existingLists.empty()) {
                existingLists[1] = name;
            }
            // When the list is not empty we simply "append" to the map
            else {
                // last corresponds to the last pair in the map (that's why rbegin is used)
                auto last = existingLists.rbegin();
                // Then we just simply insert a new key-value pair
                existingLists[last->first + 1] = name;
            }
            break;
        }
        cout << "File already exists. Please enter a valid option.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}


// ToDoList Menu: allows users to perform actions inside the selected ToDoList
int Menu::ToDoListMenu() {
    // Update todolist object so we can execute method's from ToDoList class in following methods of the class
    todolist = ToDoList(currentListName);

    cout << "===== " << currentListName << " =====\n";
    // Options from the menu
    cout << "1. Show tasks\n";
    // Add new task
    cout << "2. Add task\n";
    // Order ToDoList based on different criteria
    cout << "3. Order\n";
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


// Basic output function
void Menu::ShowToDoList() {
    todolist.OutputTasks();
}


// Functions to input a new Task
string Menu::TaskNameInput() {
    // Name field
    string name;
    // Flag
    while (true) {
        cout << "Enter the task name: ";
        /* When using getline we have to make sure that the input stream is clear
         * because cin leaves any newline or space behind so we have to skip it so we use cin.ignore*/
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (getline(cin, name)) {
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
    // User input
    int user;
    // Priority string
    string priority;
    while (true) {
        cout << "Enter the task priority (1 - HIGH | 2 - NORMAL | 3 - LOW): \n";
        if (cin >> user && user >= 1 && user <= 3) {
            // Switch case to handle different options
            switch (user) {
                case 1:
                    priority = "HIGH";
                    break;
                case 2:
                    priority = "NORMAL";
                    break;
                default:
                    priority = "LOW";
                    break;
            }
            break;
        }
        cout << "Invalid input. Please enter a valid option.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return priority;
}


string Menu::TaskStatusInput() {
    int user;
    // Name field
    string status;
    while (true) {
        cout << "Enter the task priority (1 - IN PROGRESS | 2 - TODO): \n";
        if (cin >> user && user >= 1 && user <= 2) {
            // Switch case to handle different options
            switch (user) {
                case 1:
                    status = "IN PROGRESS";
                    break;
                default:
                    status = "TODO";
                    break;
            }
            break;
        }
        cout << "Invalid input. Please enter a valid option.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return status;
}


// Add Task to the todolist object
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
    todolist.AddTask(task);
}


// Order menu according to parameter
void Menu::OrderTasks() {
    if (todolist.getTodolistSize() != 0) {
        int user;
        while (true) {
            cout << "Enter the ordering option (1 - Alphabetic order | 2 - Oldest to Newest | 3 - Newest to oldest |"
                    " 4 - Priority | 5 - Status): \n";
            if (cin >> user && user >= 1 && user <= 5) {
                // Switch case to handle different options
                switch (user) {
                    case 1:
                        todolist.AlphabeticOrder();
                        // Alphabetic order
                        break;
                    case 2:
                        // Ascending due date
                        todolist.AscendingDate();
                        break;
                    case 3:
                        // Descending due date
                        todolist.DescendingDate();
                        break;
                    case 4:
                        // Priority
                        todolist.PriorityOrder();
                        break;
                    default:
                        todolist.StatusOrder();
                        // Status
                        break;
                }
                ShowToDoList();
                break;
            }
            cout << "Invalid input. Please enter a valid option.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    else {
        cout << "No tasks found, unable to order. Let's first add some tasks\n";
    }
}


// Deletes task from todolist object
void Menu::DeleteTask() {
    if (todolist.getTodolistSize() != 0) {
        size_t user;
        while (true) {
            cout << "Enter the task number (to be deleted): ";
            // Make sure it's in the range
            if (cin >> user && user >= 1 && user <= todolist.getTodolistSize() + 1) {
                // Delete task from ToDoList and File
                todolist.DeleteTask(user);
                break;
            }
            cout << "Invalid input. Please enter a valid option.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    else {
        cout << "No tasks found, unable to delete. Let's first add some tasks\n";
    }
}


// Selects the correct field to be edited
void Menu::FieldSelector(size_t& position) {
    // User second input inside of Edit Task
    size_t fieldPosition;
    while (true) {
        cout << "Enter the field number to be edited (1 - Name | 2 - Due Date | 3 - Priority | 4 - Status): ";
        // Make sure it's in the range
        if (cin >> fieldPosition && fieldPosition >= 1 && fieldPosition <= 4) {
            switch (fieldPosition) {
                case 1:
                    todolist.EditTaskName(position, TaskNameInput());
                    break;
                case 2:
                    todolist.EditTaskDueDate(position, DateInput());
                    break;
                case 3:
                    todolist.EditTaskPriority(position, TaskPriorityInput());
                    break;
                default:
                    todolist.EditTaskStatus(position, TaskStatusInput());
                    break;
            }
            break;
        }
        cout << "Invalid input. Please enter a valid option.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}


// Function to Edit the Task
void Menu::EditTask() {
    if (todolist.getTodolistSize() != 0) {
        size_t position;
        while (true) {
            cout << "Enter the task number (to be edited): ";
            // Make sure it's in the range
            if (cin >> position && position >= 1 && position <= todolist.getTodolistSize() + 1) {
                FieldSelector(position);
                break;
            }
            cout << "Invalid input. Please enter a valid option.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    else {
        cout << "No tasks found, unable to edit. Let's first add some tasks\n";
    }
}


// Saves changes to File
void Menu::Save() {
    todolist.SaveToFile();
}

