#ifndef INVALIDDATE_H
#define INVALIDEDATE_H
#include <stdexcept>

// This class is used to, by inheritance, define the invalid date error used to verify the constructors of date.hpp
class InvalidDate : public std::logic_error {
public:
    InvalidDate(): logic_error("Invalid Date") {}
};

#endif
