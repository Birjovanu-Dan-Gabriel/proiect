#include "Singleton.h"
#include <iostream>

// Initialize the static instance to nullptr
Singleton* Singleton::instance = nullptr;

// Private constructor implementation
Singleton::Singleton() {}

// Static method to access the single instance
Singleton* Singleton::getInstance() {
    if (!instance) {
        instance = new Singleton();
    }
    return instance;
}

// Example method implementation
void Singleton::showMessage() {
    std::cout << "Singleton instance\n";
}
