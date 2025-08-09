#include "Task.hpp"
#include "InvalidField.hpp"
#include <set>
#include <utility>
#include <sstream>
using namespace std;

Task::Task() = default;

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


std::string Task::task_to_string() const {
    ostringstream out;
    // Using commas because it will be useful to write in a CSV
    out << taskName << ", " << dueDate.date_to_string() << ", " << taskPriority << ", " << taskStatus;
    return out.str();
}


void Task::to_upper_string(std::string &str) {
    for (auto& ch: str) {
        ch = static_cast<char>(toupper(ch));
    }
}


Date Task::getDueDate() const {
    return dueDate;
}


std::string Task::getTaskName() const {
    return taskName;
}


std::string Task::getTaskStatus() const {
    return taskStatus;
}


std::string Task::getTaskPriority() const {
    return taskPriority;
}
