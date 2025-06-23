#include "Date.hpp"
#include "InvalidDate.hpp"
#include <iostream>

int main() {
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

    return 0;
}

