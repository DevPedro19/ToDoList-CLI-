# ToDoList-CLI-
This is a CSV-backed ToDoList (CRUD CLI - Create, Read, Update and Delete 
Command Line Interface), that has file persistency.

## Backstory
I wrote this simple program after my first year of college and I used OOP and file managing C++ concepts 
that I've learned during my first year's second semester.
It was an interesting challenge since I've never coded a project all by myself (all the classes and how the program works was thought out by me), even though 
the end product was obviously simple.
I tried to make the code as readable and maintainable as possible.


## Build Instructions
Clone this repository and build with CMake:

```bash
# Clone the repo
git clone https://github.com/DevPedro19/ToDoList-CLI-.git
cd ToDoList-CLI-
# Build the files
cmake -B build
# Enter the build folder
cd build
# Make executables
make
# Clear to clean the terminal before running
clear
# Run the program
./main
```

## Folder structure
```
ToDoList-CLI-/
├── include/              # Header files
    ├── Date.hpp
    ├── InvalidDate.hpp
    ├── InvalidField.hpp
    ├── Menu.hpp
    ├── Task.hpp
    ├── ToDoList.hpp
├── lists/                # Directory where CSV ToDoLists are saved
├── src/                  # Source code files
    ├── Date.cpp
    ├── Menu.cpp
    ├── Task.cpp
    ├── ToDoList.cpp
├── tester/               # Testing .cpp file (deprecated)
├── .gitignore            # Standard Git ignore files
└── CMakeLists.txt        # Build configuration for CMake
```
## How it works
Let's start by dissecting what each class does exactly.
### class Menu: 
- Creates the general interface of menus that is executed in main.cpp.
- Each menu handles user input
#### Variables defined by the class:
- **existingLists**: maps out the lists into a map so it's indexed making it easier for the user
-**currentListIndex**: To-do list index inserted by the user
- **currentListName**: List name corresponding to the selected index
- **todolist**: object of the class ToDoList that essentially represents our list
#### Enums
- Used to define integer named variables that identify different menu options

### class ToDoList: 
- Defined useful functions to apply to the ToDoList (essetially a vector of Tasks)
#### Variables defined by the class:
- **filePath**: ToDoList corresponding filePath
- **fileTasks**: Vector that contains Tasks

### class Task: 
- Defines a Task as an object cointaining important properties (name, date, priority and status)
#### Variables defined by the class:
- Pretty self explanatory: **TaskName**: name, **dueDate**: date, **taskPriority**: priority (LOW, NORMAL, HIGH) and **taskStatus**: status (TODO, IN PROGRESS)

### class Date: 
- Defines a valid Date

### main.cpp
- Defines the coditional flow of the code
