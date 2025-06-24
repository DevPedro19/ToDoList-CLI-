// date.hpp
// This class is responsible for correctly defining dates for a certain task
#ifndef DATE_H
#define DATE_H

#include <string>
#include <vector>

class Date{
    public:
        Date();
        // Constructor with parameters (dd/mm/yyyy)
        Date(int day, int month, int year);
        // For debug purposes
        [[nodiscard]] std::string date_to_string() const;
        // Verify if the year is leap or non leap
        static bool is_leap(int year);
        // Check the validity of the date
        [[nodiscard]] bool is_valid() const;
    private:
        // Member fields
        int day, month, year;
        // Vector that holds the number of days of each year
        std::vector<int> monthDays = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
};

#endif