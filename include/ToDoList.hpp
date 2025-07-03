// Creates a new todolist and when the object is destroyed writes it to a Json File

#ifndef TODOLIST_H
#define TODOLIST_H

#include "Task.hpp"
#include <iostream>
// Libs to work with JSON file in C++
#include <json.hpp>
using json = nlohmann::json;

class ToDoList {
public:
    ToDoList();
    void addTask(const Task& task);
private:
    json document;
};

#endif