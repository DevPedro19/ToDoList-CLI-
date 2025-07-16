//
// Created by pedro on 7/16/25.
//

#ifndef MENU_HPP
#define MENU_HPP
#include <string>
#include <set>
using namespace std;

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
    set<string> ToDoListVector();
    // Selection Menu
    int SelectMenu();
    // Enter ToDoList name

    // Delete ToDoList
private:
    // Function to compute existingLists variable
    set<string> existingLists = ToDoListVector();
};

#endif //MENU_HPP
