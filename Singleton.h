#ifndef SINGLETON_H
#define SINGLETON_H

class Singleton {
private:
    static Singleton* instance; // Pointer to the single instance
    Singleton(); // Private constructor

public:
    // Deleting copy constructor and assignment operator
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    // Static method to access the single instance
    static Singleton* getInstance();

    // Example method to demonstrate functionality
    void showMessage();
};

#endif // SINGLETON_H
