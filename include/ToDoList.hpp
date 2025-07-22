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
    ToDoList(const string& filename);
    // Write CSV header if the file is empty
    void WriteHeader();
    // Parse CSV file
    void ParseFile();
    // Add new task to JSON file
    void AddTask(const Task& task);
    // Save info in file
    void SaveToFile();
    // Parse JSON array in file
    void OutputTasks();
    // Create static functions capable of sorting the JSON array based on different parameters
    // For example, sort the array by alphabetic order, priority or even date


    // Change task fields, for example priority changed, task status, completion

    // Remove tasks

    // Auxiliary functions
    static vector<string> GetFieldVector(string& line);
private:
    std::string filePath;
    std::vector<Task> fileTasks;

};

#endif