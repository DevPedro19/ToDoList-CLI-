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
    // Auxiliary functions
    static string TaskNameInput();
    static Date DateInput();
    static string TaskPriorityInput();
    static string TaskStatusInput();
    static string ToUpper(string& str);
private:
    map<int, string> existingLists;
    string listName;
    ToDoList todolist;
    Task currentTask;
    string path = "../lists/" + listName + ".csv";
};

#endif //MENU_HPP
