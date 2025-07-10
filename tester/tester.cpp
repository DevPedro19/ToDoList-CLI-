//
// Created by pedro on 6/24/25.
//
#include "Task.hpp"
#include "Date.hpp"
#include "InvalidField.hpp"
#include "InvalidDate.hpp"
#include <iostream>

#include "ToDoList.hpp"

int main() {

    std::cout << "------------------DATE TESTING----------------" << std::endl;
    // 1. February 29 on a non-leap year
    try {
        Date invalid_date(29, 2, 2025);  // 2025 is not a leap year
        std::cout << invalid_date.date_to_string() << std::endl;
    } catch (const InvalidDate& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }

    // 2. April 31 (April has only 30 days)
    try {
        Date invalid_date(31, 4, 2024);
        std::cout << invalid_date.date_to_string() << std::endl;
    } catch (const InvalidDate& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }

    // 3. Month out of range
    try {
        Date invalid_date(10, 13, 2024);  // Month 13 doesn't exist
        std::cout << invalid_date.date_to_string() << std::endl;
    } catch (const InvalidDate& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }

    // 4. Day 0
    try {
        Date invalid_date(0, 5, 2024);  // Day cannot be 0
        std::cout << invalid_date.date_to_string() << std::endl;
    } catch (const InvalidDate& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }

    // 5. Negative year
    try {
        Date invalid_date(15, 7, 0);  // Invalid year if negative not supported
        std::cout << invalid_date.date_to_string() << std::endl;
    } catch (const InvalidDate& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }



    std::cout << "------------------TASK TESTING----------------" << std::endl;

    // Valid Task
    try {
        Date date;
        Task new_task("Create ToDoList structure in JSON file", date, "HIGH", "TODO");
        std::cout << new_task.task_to_string() << std::endl;
    } catch (const InvalidField& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    } catch (const InvalidDate& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }


    // Invalid Date
    try {
        Date date(29, 02, 2025);
        Task new_task("Create ToDoList structure in JSON file", date, "HIGH", "TODO");
        std::cout << new_task.task_to_string() << std::endl;
    } catch (const InvalidField& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    } catch (const InvalidDate& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }

    // Invalid field (empty name)
    try {
        Date date(28, 02, 2025);
        Task new_task("", date, "HIGH", "TODO");
        std::cout << new_task.task_to_string() << std::endl;
    } catch (const InvalidField& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    } catch (const InvalidDate& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }

    // Invalid field (invalid priority)
    try {
        Date date(28, 02, 2025);
        Task new_task("Create ToDoList structure in JSON file", date, "BIG", "TODO");
        std::cout << new_task.task_to_string() << std::endl;
    } catch (const InvalidField& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    } catch (const InvalidDate& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }

    // Invalid field (invalid status)
    try {
        Date date(28, 02, 2025);
        Task new_task("Create ToDoList structure in JSON file", date, "HIGH", "done");
        std::cout << new_task.task_to_string() << std::endl;
    } catch (const InvalidField& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    } catch (const InvalidDate& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
    std::cout << "------------------Todolist TESTING----------------" << std::endl;
    try {
        Date date(3, 7, 2025);
        Task new_task("Create ToDoList structure in JSON file", date, "HIGH", "TODO");
        std::cout << new_task.task_to_string() << std::endl;
        ToDoList todolist;
        todolist.addTask(new_task);
        todolist.addTask(new_task);
        todolist.saveFile("tasks");
        todolist.outputFile("tasks");
        // Testing if adding a new tasks "resets" the info already in the file
        todolist.addTask(new_task);
        todolist.saveFile("tasks");
        todolist.outputFile("tasks");
    } catch (const InvalidField& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    } catch (const InvalidDate& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }












    return 0;
}

