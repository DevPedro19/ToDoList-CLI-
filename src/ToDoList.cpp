#include "ToDoList.hpp"
#include <iostream>
#include <fstream>

ToDoList::ToDoList() {
    document = json::array();
}

ToDoList::ToDoList(string &filename) {
    // Input file with corresponding filepath
    std::ifstream inputFile("../lists/" + filename + ".json");
    // Parsed Input File and saved in Doc json variable
    json Doc{json::parse(inputFile)};
    // document is now the parsed Doc
    document = Doc;
    fileName = filename;
}


void ToDoList::addTask(const Task &task){
    // Creates a json object containing task values
    json currentTask {
        {"taskName", task.getTaskName()},
        {"dueDate", task.getDueDate().date_to_string()},
        {"taskPriority", task.getTaskPriority()},
        {"taskStatus", task.getTaskStatus()},
    };
    // Document is a json array that stores all tasks of that file
    document.push_back(currentTask);
}

void ToDoList::saveFile() {
    // Create an object capable of writing JSON info to a JSON file, in append mode, so it doesn't erase previous info
    // It will be saved in the sub directory lists
    std::ofstream outputFile("../lists/" + fileName + ".json");
    // Output with correct indent (using dump method)
    outputFile << document.dump(4);
}

void ToDoList::outputFile() {
    std::ifstream inputFile("../lists/" + fileName + ".json");
    // Creates an iterable object of type JSON to get data and pretty print the tasks to the console
    // jsonData works like a c++ style array
    json jsonData;
    // Parsed file is now in the object
    inputFile >> jsonData;
    // Output pretty-printing the result
    std::cout << "LIST: " << fileName << std::endl;
    for (const auto& item: jsonData) {
        std::cout << item.dump(4) << std::endl;
    }
}




