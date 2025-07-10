#include "ToDoList.hpp"

using std::ios;

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

void ToDoList::saveFile(const std::string &filename) {
    // Create an object capable of writing JSON info to a JSON file, in append mode, so it doesn't erase previous info
    // It will be saved in the sub directory lists
    std::ofstream outputFile("../lists/" + filename + ".json");
    outputFile << document;
}

void ToDoList::outputFile(const std::string &filename) {
    std::ifstream ifs("../lists/" + filename + ".json");
    // Creates an iterable object of type JSON to get data and pretty print the tasks to the console
    // jsonData works like a c++ style array
    json jsonData;
    // Parsed file is now in the object
    ifs >> jsonData;
    // Output pretty-printing the result
    std::cout << "LIST: " << filename << std::endl;
    for (const auto& item: jsonData) {
        std::cout << item.dump(4) << std::endl;
    }
}




