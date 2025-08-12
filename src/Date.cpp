#include "Date.hpp"
#include "InvalidDate.hpp"
#include <iomanip>
#include <sstream>


using namespace std;

Date::Date() : day(0), month(0), year(0){}


// Constructor with parameters (dd/mm/yyyy)
Date::Date(const int day, const int month, const int year) {
    // Check "date bounds"
    if (day >= 1 && day <= 31 && month >= 1 && month <= 12 && year >= 1) {
        // If the year is leap
        if (is_leap(year)) {
            monthDays[1] = 29;
        }
        // For every month
        if (day > monthDays[month - 1]) {
            throw InvalidDate();
        }
        // Now we can initialize the member fields
        this->day = day;
        this->month = month;
        this->year = year;
    }
    else {
        throw InvalidDate();
    }
}


// Return date as a string
string Date::date_to_string() const {
    ostringstream out;
    out << setfill('0') << setw(2) << day << '/' << setw(2) << month << '/' << setw(4) << year;
    return out.str();
}


bool Date::is_leap(int year) {
    // A year is a leap year if divisible by 4 and not by 100, or divisible by 400
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}


bool Date::is_valid() const {
    bool res = false;
    if (day == 0 && month == 0 && year == 0) {
        res = true;
    }
    return res;
}


int Date::getDay() const {
    return day;
}

int Date::getMonth() const {
    return month;
}

int Date::getYear() const {
    return year;
}

bool Date::operator<(const Date &date) const {
    if (year != date.year) return year < date.year;
    if (month != date.month) return month < date.month;
    return day < date.day;
}

