//
// Created by birjo on 12/3/2024.
//

#include "Exceptions.h"

#include <utility>


// Constructor
MyException::MyException(std::string  msg) : message(std::move(msg)) {}

const char* MyException::what() const noexcept {
    return message.c_str();
}

// Derived classes constructors

//file error
FileNotFoundException::FileNotFoundException(const std::string& filename)
    : MyException("File not found: " + filename) {}

//input error
InvalidInputException::InvalidInputException(const std::string& input)
    : MyException("Invalid input: " + input) {}

//calculation error
CalculationException::CalculationException(const std::string& details)
    : MyException("Calculation error: " + details) {}
