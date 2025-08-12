#include "ToDoList.hpp"
#include <fstream>
#include <iostream>
#include <filesystem>
#include <algorithm>
using std::ifstream;
using std::ofstream;
using std::filesystem::is_empty;
using std::getline;
using std::vector;
using std::istringstream;
using std::cout;
using std::sort;


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
    // Add to file
    ofstream output(filePath, std::ios::app);
    // Only write to the file the last task
    output << fileTasks.back().task_to_string() << '\n';
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
    // Delete task from file
    ifstream ifs(filePath);
    // Current line
    string line;
    // Result of "cutting and gluing back the file"
    string res;
    bool first_line = true;
    // Basically in this loop we only add the lines that do not correspond to the task to delete
    while (getline(ifs, line)) {
        if (first_line) {
            res += line + '\n';
        }
        else {
            // Substring methods to only get the taskName
            string taskName = line.substr(0, line.find_first_of(','));
            if (delTask.getTaskName() != taskName) {
                res += line + '\n';
            }
        }
        first_line = false;
    }
    // Output file stream that allows us to write to the file
    ofstream ofs(filePath);
    ofs << res;
}

size_t ToDoList::getTodolistSize() {
    // Gets the ToDoList size
    return fileTasks.size();
}
