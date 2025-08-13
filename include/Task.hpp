#ifndef TASK_H
#define TASK_H
#include "Date.hpp"
#include <unordered_map>

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

#endif
