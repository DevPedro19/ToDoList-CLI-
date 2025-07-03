//
// Created by pedro on 6/24/25.
//

#ifndef INVALIDFIELD_HPP
#define INVALIDFIELD_HPP
#include <stdexcept>

// This class is used to, by inheritance, define the invalid date error used to verify the constructors of date.hpp
class InvalidField : public std::logic_error {
public:
    explicit InvalidField(const std::string& field): logic_error("Invalid " + field) {}
};

#endif //INVALIDFIELD_HPP
