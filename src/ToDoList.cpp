#include "ToDoList.hpp"
#include <fstream>
#include <iostream>
#include <filesystem>

using std::ifstream;
using std::ofstream;
using std::filesystem::is_empty;
using std::getline;
using std::vector;
using std::istringstream;
using std::cout;


// Trivial constructor
ToDoList::ToDoList() = default;


ToDoList::ToDoList(const string &filename) {
    filePath = "../lists/" + filename + ".csv";
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
        ofs << "Name, Due Date, Priority, Status";
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
        // If the line is not the header, or it doesn't contain any of the header names
        vector<string> fields;
        if (!first_line || line.find("Name") == string::npos) {
            fields = GetFieldVector(line);
        }
        first_line = false;
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
}


// Add new task to file
void ToDoList::AddTask(const Task &task){
    fileTasks.push_back(task);
}

// Save info in file
void ToDoList::SaveToFile() {
    ofstream output(filePath);
    for (auto& task : fileTasks) {
        output << task.task_to_string() << '\n';
    }
}

// Pretty print the current tasks
void ToDoList::OutputTasks() {
    cout << "===== Tasks in file =====\n";
    for (auto& task : fileTasks) {
        cout << task.task_to_string() << '\n';
    }
    cout << '\n';
}

// TODO: Create overloads to sort the tasks to be displayed

// TODO: Create functions that use those overloads to sort tasks inside a ToDoList object

