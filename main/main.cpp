#include "Menu.hpp"

int main() {
    // Create menu object
    Menu menu;
    // Get user selection
    int userIntroMenu = menu.IntroMenu();
    // Option selected
    if (userIntroMenu == CHECK) {
        // Set with lists names
        set<string> lists = menu.ToDoListVector();
        // Display existing lists
        menu.SelectMenu();
    }
    return 0;
}