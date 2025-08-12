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

    // This loop will only repeat if we are doing add or delete
    while (userSelectMenu != SELECT_EXIT && userIntroMenu != INTRO_EXIT) {
        // User selection for select menu
        if (userSelectMenu == SELECT) {
            // Find corresponding list
            menu.FindToDoList();
            // Get user option
            userToDoListMenu = menu.ToDoListMenu();
            break;
        }

        if (userSelectMenu == DELETE) {
            // Find corresponding list
            menu.FindToDoList();
            // Delete list
            menu.DeleteToDoList();
        }

        if (userSelectMenu == ADD_LIST) {
            // Creates a new ToDoList
            menu.AddNewToDoList();
        }
        userSelectMenu = menu.SelectMenu();
    }


    // Only executes the loop if previous user inputs were not to exit the program
    while (userToDoListMenu != TD_EXIT && userIntroMenu != INTRO_EXIT && userSelectMenu != SELECT_EXIT) {
        // User Selection for ToDoList Menu
        if (userToDoListMenu == SHOW) {
            // Show ToDoList
            menu.ShowToDoList();
        }
        if (userToDoListMenu == ADD) {
            // Add new task to ToDoList
            menu.AddTask();
        }
        if (userToDoListMenu == ORDER) {
            menu.OrderTasks();
        }
        if (userToDoListMenu == REMOVE) {
            // Show the real order of the tasks
            menu.ShowToDoList();
            menu.DeleteTask();
        }
        // Show menu again and restart the loop
        userToDoListMenu = menu.ToDoListMenu();
    }
}