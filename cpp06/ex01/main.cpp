#include "Serialization.hpp"
#include <iostream>

int main()
{
    Data myData;
    myData.id = 42;
    myData.name = "42";

    std::cout << "--- ORIGINAL DATA ---" << std::endl;
    std::cout << "Memory Address: " << &myData << std::endl;
    std::cout << "ID: " << myData.id << ", Name: " << myData.name << "\n" << std::endl;

    uintptr_t rawAddress = Serializer::serialize(&myData);
    
    std::cout << "--- SERIALIZATION ---" << std::endl;
    std::cout << "(uintptr_t): " << rawAddress << "\n" << std::endl;

    Data* deserializedPtr = Serializer::deserialize(rawAddress);

    std::cout << "--- DESERIALIZATION ---" << std::endl;
    std::cout << "New Address: " << deserializedPtr << std::endl;
    
    if (deserializedPtr == &myData)
    {
        std::cout << "\nSUCCESS!" << std::endl;
        std::cout << "ID: " << deserializedPtr->id 
                  << ", Name: " << deserializedPtr->name << std::endl;
    }
    else
    {
        std::cout << "\nERROR!" << std::endl;
    }

    return 0;
}