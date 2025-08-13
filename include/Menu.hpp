//
// Created by pedro on 7/16/25.
//

#ifndef MENU_HPP
#define MENU_HPP
#include "ToDoList.hpp"
#include <string>
#include <map>
using std::map;
using std::string;

// Enums for different MENUS (in Menu.hpp so it can used inside the class and also in main.cpp)
enum IntroMenu{CHECK = 1, INTRO_EXIT = 2};
enum SelectMenu {SELECT = 1, DELETE = 2, ADD_LIST = 3, SELECT_EXIT = 4 };
enum ToDoListMenu{SHOW = 1, ADD = 2, ORDER = 3, REMOVE = 4, EDIT = 5, TD_EXIT = 6};
enum Priority{HIGH = 1, NORMAL = 2, LOW = 3};

class Menu {
public:
    // Default constructor
    Menu();
    // Intro menu
    int IntroMenu();
    // Creates a vector containing ToDoList .csv files
    void ToDoListMap();
    // Selection Menu
    int SelectMenu();
    // Find the corresponding list
    void FindToDoList();
    // Checks if the name already exists
    bool FoundName(string& name);
    // Delete the corresponding ToDoList
    void DeleteToDoList();
    // Add a new ToDoList
    void AddNewToDoList();
    // Enter the ToDoList to proceed with other operations
    int ToDoListMenu();
    // Show ToDoList
    void ShowToDoList();
    // Add task to ToDoList via menu
    void AddTask();
    // Order menu
    void OrderTasks();
    // Delete task
    void DeleteTask();
    // Edit task
    void EditTask();
    // Field Selector
    void FieldSelector(size_t& position);
    // Save in file
    void Save();
    // Auxiliary functions
    static string TaskNameInput();
    static Date DateInput();
    static string TaskPriorityInput();
    static string TaskStatusInput();
private:
    map<int, string> existingLists;
    // Current list index
    int currentListIndex = 0;
    // Current List name
    string currentListName;
    ToDoList todolist;
};

#endif //MENU_HPP
