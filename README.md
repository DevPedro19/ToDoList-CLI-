# ToDoList-CLI-
This is a CSV-backed ToDoList (CRUD CLI - Create, Read, Update and Delete 
Command Line Interface).

## Build Instructions
Clone this repository and build with CMake:

```bash
# Clone the repo
git clone git@github.com:DevPedro19/ToDoList-CLI-.git
cd ToDoList-CLI-
# Build the files
cmake -B build
# Enter the build folder
cd build
# Make executables
make
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



## Backstory
I wrote this simple program after my first year of college and I used OOP C++ concepts 
that I've learned during my first year's second semester.
It was an interesting challenge since I've never coded a project all by myself, even though 
the end product was obviously simple.
I tried to make the code as readable and maintainable as possible.
