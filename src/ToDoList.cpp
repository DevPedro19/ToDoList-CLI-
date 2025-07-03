#include "ToDoList.hpp"

ToDoList::ToDoList() {
    document = json::array();
}

void ToDoList::addTask(const Task &task){
    json currentTask {
        {"taskName", task.getTaskName()},
        {"dueDate", task.getDueDate().date_to_string()},
        {"taskPriority", task.getTaskPriority()},
        {"taskStatus", task.getTaskStatus()},
    };

    document.push_back(currentTask);
}


