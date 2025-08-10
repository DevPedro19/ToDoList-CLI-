#ifndef TASK_H
#define TASK_H
#include "Date.hpp"

class Task {
public:
    Task();
    // Constructor with parameters
    Task(std::string& name, Date& due, std::string& priority, std::string& stat);
    // Normalise string
    static void to_upper_string(std::string& str);
    // For testing purposes
    [[nodiscard]] std::string task_to_string() const;
    // Getters
    [[nodiscard]] std::string getTaskName() const;
    [[nodiscard]] Date getDueDate() const;
    [[nodiscard]] std::string getTaskPriority() const;
    [[nodiscard]] std::string getTaskStatus() const;
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

#endif
