#include <iostream>
#include <string>
#include "Array.hpp"

int main()
{
    std::cout << "--- 1. Default Constructor Test ---\n";
    Array<int> emptyArray;
    std::cout << "Empty array size: " << emptyArray.size() << "\n\n";



    std::cout << "--- 2. Parameterized Constructor Test ---\n";
    Array<int> intArray(5);
    std::cout << "intArray size: " << intArray.size() << "\n";
    for (unsigned int i = 0; i < intArray.size(); i++)
    {
        std::cout << "intArray[" << i << "] = " << intArray[i] << "\n";
    }
    std::cout << "\n";



    std::cout << "--- 3. Assignment (Write) Test ---\n";
    for (unsigned int i = 0; i < intArray.size(); i++) {
        intArray[i] = i * 10;
        std::cout << "New intArray[" << i << "] = " << intArray[i] << "\n";
    }
    std::cout << "\n";



    std::cout << "--- 4. Copy Constructor (Deep Copy) Test ---\n";
    Array<int> copyArray(intArray);
    std::cout << "Copy created. Modifying original array...\n";
    intArray[0] = 999;
    std::cout << "Original array intArray[0]: " << intArray[0] << "\n";
    std::cout << "Copied array copyArray[0] : " << copyArray[0] << "\n\n";



    std::cout << "--- 5. Out of Bounds Exception Test ---\n";
    try
    {
        std::cout << "Trying to access index 10 of intArray...\n";
        std::cout << intArray[10] << "\n";
        std::cout << "This line should never be printed!\n";
    }
    catch (const std::exception& e)
    {
        std::cout << "Exception caught: " << e.what() << "\n";
    }
    std::cout << "\n";



    std::cout << "--- 6. Different Data Type (std::string) Test ---\n";
    Array<std::string> stringArray(3);
    stringArray[0] = "Hello";
    stringArray[1] = "C++";
    stringArray[2] = "42";
    for (unsigned int i = 0; i < stringArray.size(); i++)
    {
        std::cout << "stringArray[" << i << "] = " << stringArray[i] << "\n";
    }

    return 0;
}