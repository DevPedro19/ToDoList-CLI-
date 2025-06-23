// date.hpp
// This class is responsible for correctly defining dates for a certain task
#ifndef DATE_H
#define DATE_H

#include <string>
#include <vector>

class Date{
    public:
        // Constructor with parameters (dd/mm/yyyy)
        Date(int day, int month, int year);
        // Return date as a string
        [[nodiscard]] std::string date_to_string() const;
        // Verify if the year is leap or non leap
        static bool is_leap(int year) ;
    private:
        int day, month, year;
        std::vector<int> monthDays = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
};

#endif