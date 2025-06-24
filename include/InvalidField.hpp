//
// Created by pedro on 6/24/25.
//

#ifndef INVALIDFIELD_HPP
#define INVALIDFIELD_HPP
#include <stdexcept>

// This class is used to, by inheritance, define the invalid date error used to verify the constructors of date.hpp
class InvalidField : public std::logic_error {
public:
    InvalidField(): logic_error("Invalid Field") {}
};

#endif //INVALIDFIELD_HPP
