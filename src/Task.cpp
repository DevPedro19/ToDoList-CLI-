#include "Task.hpp"
#include "InvalidField.hpp"
#include <set>
#include <utility>
#include <sstream>

// Global variables to the class
std::unordered_map<std::string, int> Task::PriorityMap = {
    {"HIGH", 0}, {"NORMAL", 1}, {"LOW", 2}
};

std::unordered_map<std::string, int> Task::StatusMap = {
    {"TODO", 0}, {"IN PROGRESS", 1},
};

Task::Task() = default;


// Constructor with exeption handlers
Task::Task(std::string& name, Date& due, std::string& priority, std::string& stat): dueDate(std::move(due)) {
    // Check if values are correct

    // Check if task name is non empty
    !name.empty() ? taskName = name : throw InvalidField("taskName");

    // Normalise the input for priority
    to_upper_string(priority);

    // Check if priority is valid
    std::set<std::string> priorities = {"HIGH", "NORMAL", "LOW"};
    priorities.find(priority) != priorities.end() ? taskPriority = priority : throw InvalidField("taskPriority");

    // Normalise the input for status
    to_upper_string(stat);

    // Check if status is valid
    std::set<std::string> status = {"IN PROGRESS", "TODO"};
    status.find(stat) != status.end() ? taskStatus = stat : throw InvalidField("taskStatus");

}


// Outputs the task as a string
std::string Task::task_to_string() const {
    std::ostringstream out;
    // Using commas because it will be useful to write in a CSV
    out << taskName << ", " << dueDate.date_to_string() << ", " << taskPriority << ", " << taskStatus;
    return out.str();
}


// to upper function
void Task::to_upper_string(std::string &str) {
    for (auto& ch: str) {
        ch = static_cast<char>(toupper(ch));
    }
}


// Getters
Date& Task::getDueDate() {
    return dueDate;
}


std::string& Task::getTaskName() {
    return taskName;
}


std::string& Task::getTaskStatus() {
    return taskStatus;
}


std::string& Task::getTaskPriority() {
    return taskPriority;
}


// Comparison functions useful for sorting tasks inside todolist object
bool Task::AlphabeticCompare(const Task &a, const Task &b) {
    return a.taskName < b.taskName;
}


bool Task::DateCompare(const Task &a, const Task &b) {
    return a.dueDate < b.dueDate;
}


bool Task::PriorityCompare(const Task &a, const Task &b) {
    return PriorityMap[a.taskPriority] < PriorityMap[b.taskPriority];
}


bool Task::StatusCompare(const Task &a, const Task &b) {
    return StatusMap[a.taskStatus] < StatusMap[b.taskStatus];
}
