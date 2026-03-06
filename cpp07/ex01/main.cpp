#include <iostream>
#include <string>
#include "iter.hpp"

template <typename T>
void printElement(const T& element)
{
    std::cout << element << " ";
}

template <typename T>
void incrementElement(T& element)
{
    element++;
}

int main()
{
    int intArray[] = {1, 2, 3, 4, 5};
    std::size_t intLength = 5;

    std::cout << "Original int array: ";
    ::iter(intArray, intLength, printElement<int>);
    std::cout << std::endl;

    ::iter(intArray, intLength, incrementElement<int>);
    
    std::cout << "Int array after increment: ";
    ::iter(intArray, intLength, printElement<int>);
    std::cout << "\n\n";

    std::string stringArray[] = {"Hello", "C++", "42"};
    std::size_t stringLength = 3;

    std::cout << "Original string array: ";
    ::iter(stringArray, stringLength, printElement<std::string>);
    std::cout << std::endl;

    return 0;
}