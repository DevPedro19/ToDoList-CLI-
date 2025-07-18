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
        userToDoListMenu = menu.ToDoListMenu();
    }

    if (userSelectMenu == DELETE) {
        // Find corresponding list
        menu.FindToDoList();
        // Delete list
        menu.DeleteToDoList();
    }

    while (userToDoListMenu != TD_EXIT) {
        // User Selection for ToDoList Menu
        if (userToDoListMenu == SHOW) {
            // Show ToDoList
            menu.ShowToDoList();
        }
        // Show menu again and restart the loop
        userToDoListMenu = menu.ToDoListMenu();
    }
}