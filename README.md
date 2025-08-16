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
```c++
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
```
#### Variables defined by the class:
- **existingLists**: maps out the lists into a map so it's indexed making it easier for the user
-**currentListIndex**: To-do list index inserted by the user
- **currentListName**: List name corresponding to the selected index
- **todolist**: object of the class ToDoList that essentially represents our list
#### Enums
- Used to define integer named variables that identify different menu options

### class ToDoList: 
- Defined useful functions to apply to the ToDoList (essetially a vector of Tasks)
```c++
class ToDoList {
public:
    // Create empty JSON array of tasks
    ToDoList();
    // Copy constructor from a file
    explicit ToDoList(const string& filename);
    // Write CSV header if the file is empty
    void WriteHeader();
    // Parse CSV file
    void ParseFile();
    // Parse Date
    static Date ParseDate(string& date);
    // Add new task to CSV file
    void AddTask(const Task& task);
    // Parse JSON array in file
    void OutputTasks();
    // Order alphabetically
    void AlphabeticOrder();
    // Order by date ascending
    void AscendingDate();
    // Order by date descending
    void DescendingDate();
    // Order by priority (higher priority on top)
    void PriorityOrder();
    // Order by status (to_do in front of in process)
    void StatusOrder();
    // Remove tasks
    size_t getTodolistSize();
    void DeleteTask(size_t& user);
    // Edit string fields of the task
    void EditTaskName(size_t& position, string str);
    void EditTaskDueDate(size_t& position, Date date);
    void EditTaskPriority(size_t& position, string str);
    void EditTaskStatus(size_t& position, string str);
    // Save to file
    void SaveToFile();
    // Auxiliary functions
    static vector<string> GetFieldVector(string& line);
private:
    std::string filePath;
    std::vector<Task> fileTasks;
};
```
#### Variables defined by the class:
- **filePath**: ToDoList corresponding filePath
- **fileTasks**: Vector that contains Tasks

### class Task: 
- Defines a Task as an object cointaining important properties (name, date, priority and status)
```c++
class Task {
public:
    Task();
    // Constructor with parameters
    Task(std::string& name, Date& due, std::string& priority, std::string& stat);
    // Normalise string
    static void to_upper_string(std::string& str);
    // To write the formatted task to our file
    [[nodiscard]] std::string task_to_string() const;
    // Mutable getters
    [[nodiscard]] std::string& getTaskName();
    [[nodiscard]] Date& getDueDate();
    [[nodiscard]] std::string& getTaskPriority();
    [[nodiscard]] std::string& getTaskStatus();
    // Static functions
    static bool AlphabeticCompare(const Task& a, const Task& b);
    static bool DateCompare(const Task& a, const Task& b);
    static bool PriorityCompare(const Task& a, const Task& b);
    static bool StatusCompare(const Task& a, const Task& b);
    // Static (global class variables)
    static::std::unordered_map<std::string, int> PriorityMap;
    static::std::unordered_map<std::string, int> StatusMap;
private:
    // Task name (Non-empty)
    std::string taskName;
    // Due date (dd/mm/yyyy)
    Date dueDate;
    // Task priority (LOW, NORMAL, HIGH)
    std::string taskPriority;
    // Status (IN PROGRESS, TODO)
    std::string taskStatus;
};
```
#### Variables defined by the class:
- Pretty self explanatory: **TaskName**: name, **dueDate**: date, **taskPriority**: priority (LOW, NORMAL, HIGH) and **taskStatus**: status (TODO, IN PROGRESS)

### class Date: 
- Defines a valid Date
```c++
class Date{
    public:
        Date();
        // Constructor with parameters (dd/mm/yyyy)
        Date(int day, int month, int year);
        // For debug purposes and to add date to the JSON file
        [[nodiscard]] std::string date_to_string() const;
        // Verify if the year is leap or non leap
        static bool is_leap(int year);
        // Check the validity of the date
        [[nodiscard]] bool is_valid() const;
        [[nodiscard]] int getDay() const;
        [[nodiscard]] int getMonth() const;
        [[nodiscard]] int getYear() const;
        // Overload for the less than comparison
        bool operator<(const Date& date) const;
    private:
        // Member fields
        int day, month, year;
        // Vector that holds the number of days of each year
        std::vector<int> monthDays = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
};
```

### main.cpp
- Defines the coditional flow of the code
