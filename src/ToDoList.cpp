#include "ToDoList.hpp"
#include <iostream>
#include <fstream>
#include <filesystem>

using std::ifstream;
using std::ofstream;
using std::filesystem::is_empty;
using std::getline;
using std::vector;


// Trivial constructor
ToDoList::ToDoList() = default;


ToDoList::ToDoList(const string &filename) {
    filePath = "../lists/" + filename + ".csv";
    // Writes the header in the CSV
    WriteHeader();
    // Parse current file
    ParseFile();

}


void ToDoList::WriteHeader() {
    // Checks if the file is empty
    if (is_empty(filePath)) {
        // Writes the CSV Header
        ofstream ofs(filePath);
        // Write to the file
        ofs << "Name, Due Date, Priority, Status";
    }
}


vector<string> ToDoList::GetFieldVector(string& line) {
    vector<string> fields;
    // Parse individual fields (I've already coded something like this before... a split or smth)
    size_t commaPosition = line.find(',');
    size_t startPosition = 0;
    while (commaPosition != string::npos) {
        // Get substring between previous comma and next comma
        string substring = line.substr(startPosition, commaPosition - startPosition);
        // Pushback to the vector
        fields.push_back(substring);
        // Start position is now the next char after the comma and the space, and thus the +2
        startPosition = commaPosition + 2;
        // Restart the search, updating the condition inside the loop
        commaPosition = line.find(',', startPosition);
    }
    // last field
    string last = line.substr(startPosition, line.length() - startPosition);
    fields.push_back(last);
    return fields;
}



void ToDoList::ParseFile() {
    // Create a parser for CSV files
    // Input filestream
    ifstream ifs(filePath);
    // Current line
    string line;
    bool first_line = true;
    while (getline(ifs, line)) {
        // If the line is not the header or it doesn't contain any of the header names
        vector<string> fields;
        if (!first_line || line.find("Name") == string::npos) {
            fields = GetFieldVector(line);
        }
        first_line = false;
        // Task fields
        string name = fields[0];
        // Have to code new constructor for Date and change some things
        string date = fields[1];
        string priority = fields[2];
        string status = fields[3];
    }
}



void ToDoList::AddTask(const Task &task){
    // Add new task to file
}


void ToDoList::SaveToFile() {

}

void ToDoList::OutputTasks() {

}

