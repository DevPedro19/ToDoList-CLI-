#include "ToDoList.hpp"
#include <fstream>
#include <iostream>
#include <filesystem>
#include <algorithm>
#include <utility>
using std::ifstream;
using std::ofstream;
using std::filesystem::is_empty;
using std::getline;
using std::vector;
using std::istringstream;
using std::cout;
using std::sort;
using std::ios;

// Trivial constructor
ToDoList::ToDoList() = default;


ToDoList::ToDoList(const string &filename) {
    filePath = "lists/" + filename + ".csv";
    // Writes the header in the CSV
    WriteHeader();
    // Parse current file
    ParseFile();
}


void ToDoList::WriteHeader() {
    // Checks if the file is empty
    if (is_empty(filePath)) {
        // Writes the CSV Header
        ofstream ofs(filePath);
        // Write to the file
        ofs << "Name, Due Date, Priority, Status \n";
    }
}


vector<string> ToDoList::GetFieldVector(string& line) {
    vector<string> fields;
    // Parse individual fields (I've already coded something like this before... a split or smth)
    size_t commaPosition = line.find(',');
    size_t startPosition = 0;
    while (commaPosition != string::npos) {
        // Get substring between previous comma and next comma
        string substring = line.substr(startPosition, commaPosition - startPosition);
        // Pushback to the vector
        fields.push_back(substring);
        // Start position is now the next char after the comma and the space, and thus the +2
        startPosition = commaPosition + 2;
        // Restart the search, updating the condition inside the loop
        commaPosition = line.find(',', startPosition);
    }
    // last field
    string last = line.substr(startPosition, line.length() - startPosition);
    fields.push_back(last);
    return fields;
}


Date ToDoList::ParseDate(string& date) {
    char sep1, sep2;
    int day, month, year;
    istringstream iss(date);
    iss >> day >> sep1 >> month >> sep2 >> year;
    return {day, month, year};
}


void ToDoList::ParseFile() {
    // Create a parser for CSV files
    // Input filestream
    ifstream ifs(filePath);
    // Current line
    string line;
    bool first_line = true;
    while (getline(ifs, line)) {
        vector<string> fields;
        if (!first_line) {
            fields = GetFieldVector(line);
            // Task fields
            string name = fields[0];
            string dateStr = fields[1];
            // Correctly parsed date to use the constructor
            Date date = ParseDate(dateStr);
            string priority = fields[2];
            string status = fields[3];
            // Create new task (constructor to implement)
            auto newTask = Task(name, date, priority, status);
            // Add task to the vector of the class
            fileTasks.push_back(newTask);
        }
        first_line = false;
    }
}


// Add new task to file
void ToDoList::AddTask(const Task &task){
    // Add to ToDoList
    fileTasks.push_back(task);
}

// Pretty print the current tasks
void ToDoList::OutputTasks() {
    cout << "===== Tasks in file =====\n";
    int counter = 1;
    for (auto& task : fileTasks) {
        cout << counter << ". " << task.task_to_string() << '\n'; counter++;
    }
    cout << '\n';
}


void ToDoList::AlphabeticOrder() {
    sort(fileTasks.begin(), fileTasks.end(), Task::AlphabeticCompare);
}

void ToDoList::AscendingDate() {
    sort(fileTasks.begin(), fileTasks.end(), Task::DateCompare);
}

void ToDoList::DescendingDate() {
    sort(fileTasks.begin(), fileTasks.end(), Task::DateCompare);
    reverse(fileTasks.begin(), fileTasks.end());
}

void ToDoList::PriorityOrder() {
    sort(fileTasks.begin(), fileTasks.end(), Task::PriorityCompare);
}

void ToDoList::StatusOrder() {
    sort(fileTasks.begin(), fileTasks.end(), Task::StatusCompare);
}

void ToDoList::DeleteTask(size_t& user) {
    Task delTask = fileTasks.at(user - 1);
    // Delete task from fileTasks vector (indexable)
    fileTasks.erase(fileTasks.begin() + static_cast<int>(user) - 1);
}

size_t ToDoList::getTodolistSize() {
    // Gets the ToDoList size
    return fileTasks.size();
}


void ToDoList::EditTaskName(size_t &position, string str) {
    // Access the task through its index and then use the mutable reference to change the value of the field we want
    fileTasks.at(position - 1).getTaskName() = std::move(str);
}


void ToDoList::EditTaskDueDate(size_t &position, Date date) {
    fileTasks.at(position - 1).getDueDate() = std::move(date);
}


void ToDoList::EditTaskPriority(size_t &position, string str) {
    fileTasks.at(position - 1).getTaskPriority() = std::move(str);
}


void ToDoList::EditTaskStatus(size_t &position, string str) {
    fileTasks.at(position - 1).getTaskStatus() = std::move(str);
}


void ToDoList::SaveToFile() {
    // Truncate the file completely
    ofstream trunc(filePath, ios::trunc);
    // First write the header
    WriteHeader();
    // Create object to output file (we will overwrite the file, truncating the initial content)
    ofstream output(filePath, ios::app);
    // Then output all the tasks to the file correctly
    for (auto& task: fileTasks) {
        output << task.task_to_string() << '\n';
    }
}
