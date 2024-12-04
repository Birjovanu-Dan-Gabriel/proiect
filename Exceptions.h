//
// Created by birjo on 12/3/2024.
//

#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H



#include <exception>
#include <string>

// Clasa de bază pentru excepții personalizate
class MyException : public std::exception {
protected:
    std::string message;
public:
    explicit MyException(std::string  msg);
    [[nodiscard]] const char* what() const noexcept override;
};

// Clase derivate pentru tipuri specifice de excepții
class FileNotFoundException : public MyException {
public:
    explicit FileNotFoundException(const std::string& filename);
};

class InvalidInputException : public MyException {
public:
    explicit InvalidInputException(const std::string& input);
};

class CalculationException : public MyException {
public:
    explicit CalculationException(const std::string& details);
};



#endif //EXCEPTIONS_H
