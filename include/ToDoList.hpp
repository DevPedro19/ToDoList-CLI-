// Creates a new todolist and when the object is destroyed writes it to a Json File

#ifndef TODOLIST_H
#define TODOLIST_H

#include "Task.hpp"
#include <string>
using std::string;
using std::vector;

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
    // TODO: Change task fields, for example priority changed, task status, completion
    // Auxiliary functions
    static vector<string> GetFieldVector(string& line);
private:
    std::string filePath;
    std::vector<Task> fileTasks;

};

#endif