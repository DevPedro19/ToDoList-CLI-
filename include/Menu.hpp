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
enum SelectMenu {SELECT = 1, DELETE = 2, SELECT_EXIT = 3 };

class Menu {
public:
    // Default constructor
    Menu();
    // Intro menu
    int IntroMenu();
    // Creates a vector containing ToDoList .json files
    void ToDoListMap();
    // Selection Menu
    int SelectMenu();
    // Find the corresponding list
    void FindToDoList();
    // Enter the ToDoList to proceed with other operations
    void ToDoListMenu();
    // Delete ToDoList
private:
    map<int, string> existingLists;
    string listName;
    ToDoList todolist;
};

#endif //MENU_HPP
