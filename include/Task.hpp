#ifndef TASK_H
#define TASK_H
#include "Date.hpp"
// TODO : implement the rest of the class

class Task {
public:
    // Constructor with parameters
    Task(std::string& name, Date& due, std::string& priority, std::string& status);
    // Turn task into string
    std::string task_to_string() const;
private:
    // Task name
    std::string taskName;
    // Due date
    Date dueDate;
    // Task priority (LOW, NORMAL, HIGH)
    std::string taskPriority;
    // Status
    std::string status;
};

#endif
