// Creates a new todolist and when the object is destroyed writes it to a Json File

#ifndef TODOLIST_H
#define TODOLIST_H

#include "Task.hpp"
#include <string>
// Libs to work with JSON file in C++
#include <json.hpp>
using std::string;
using json = nlohmann::json;

class ToDoList {
public:
    // Create empty JSON array of tasks
    ToDoList();
    // Copy constructor from a file
    ToDoList(string& filename);
    // Add new task to JSON file
    void addTask(const Task& task);
    // Save info in file
    // Make the file saved more readable
    void saveFile(const std::string& filename);
    // Parse JSON array in file
    void outputFile(const std::string& filename);
    // Create static functions capable of sorting the JSON array based on different parameters
    // For example, sort the array by alphabetic order, priority or even date


    // Change task fields, for example priority changed, task status, completion

    // Remove tasks

    // Delete JSON files in lists directory
private:
    json document;
};

#endif