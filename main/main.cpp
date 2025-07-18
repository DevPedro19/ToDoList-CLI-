#include "Menu.hpp"

int main() {
    // Create menu object
    Menu menu;

    int userIntroMenu = menu.IntroMenu();

    int userSelectMenu = 0;

    // User selection from intro menu
    if (userIntroMenu == CHECK) {
        // Map with list's names
        menu.ToDoListMap();
        // Display menu for selecting ToDoList
        userSelectMenu = menu.SelectMenu();
    }

    int userToDoListMenu = 0;

    // User selection for select menu
    if (userSelectMenu == SELECT) {
        // Find corresponding list
        menu.FindToDoList();
        menu.ToDoListMenu();
        userToDoListMenu = menu.ToDoListMenu();
    }

    if (userSelectMenu == DELETE) {
        // Delete list from lists folder
        menu.FindToDoList();
        menu.DeleteToDoList();
    }

    while (userToDoListMenu != TD_EXIT) {
        // User Selection for ToDoList Menu
        if (userToDoListMenu == SHOW) {



        }
        // Show menu again and restart the loop
        userToDoListMenu = menu.ToDoListMenu();
    }
}