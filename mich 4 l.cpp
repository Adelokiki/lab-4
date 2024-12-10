#include <iostream>
#include <stdexcept>
#include <vector>
// Base class for Transportation
class Transportation {
public:
    virtual void info() const = 0; // pure virtual function
    virtual ~Transportation() {} // virtual destructor
};
// Derived class: Bicycle
class Bicycle : public Transportation {
public:
    void info() const override {
        std::cout << "This is a bicycle." << std::endl;
    }
};
// Derived class: Car
class Car : public Transportation {
public:
    void info() const override {
        std::cout << "This is a car." << std::endl;
    }
};
// Derived class: Truck
class Truck : public Transportation {
public:
    void info() const override {
        std::cout << "This is a truck." << std::endl;
    }
};
// Template class to hold an array of pointers to objects of any class
template <typename T>
class ArrayHolder {
private:
    std::vector<T*> arr; // Vector to hold pointers of type T
public:
    // Add an object to the array
    void add(T* object) {
        arr.push_back(object);
    }
    // Overload the operator []
    T* operator[](size_t index) {
        if (index >= arr.size()) {
            throw std::out_of_range("Index out of range"); // throw exception if index is invalid
        }
        return arr[index];
    }
    // Destructor to free memory
    ~ArrayHolder() {
        for (auto ptr : arr) {
            delete ptr; // delete each pointer to free memory
        }
    }
};
int main() {
    ArrayHolder<Transportation> transportationArray;
    // Creating different transportation objects
    Transportation* bike = new Bicycle();
    Transportation* car = new Car();
    Transportation* truck = new Truck();
    // Adding objects to the array
    transportationArray.add(bike);
    transportationArray.add(car);
    transportationArray.add(truck);
    // Accessing and using the transportation objects
    std::cout << "Transportation Information:" << std::endl;
    for (size_t i = 0; i < 3; i++) {
        try {
            transportationArray[i]->info(); // show information about each transportation
        } catch (const std::out_of_range& e) {
            std::cerr << e.what() << std::endl; // catch exceptions and print error message
        }
    }

    // Accessing index out of bounds to demonstrate exception handling
    try {
        transportationArray[3]->info(); // This will throw an exception
    } catch (const std::out_of_range& e) { 
        // Catch and print the exception message
        std::cerr << e.what() << std::endl;
    }
    return 0; 
}
