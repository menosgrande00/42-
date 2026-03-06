#include "Base.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

Base* generate(void);
void identify(Base* p);
void identify(Base& p);

int main()
{
    std::srand(std::time(NULL));

    std::cout << "----------------------" << std::endl;

    for (int i = 0; i < 3; i++)
    {
        std::cout << "\n[" << i + 1 << ". TEST]" << std::endl;

        Base* randomObject = generate();

        std::cout << "Cast detection with pointer: ";
        identify(randomObject);

        std::cout << "Cast detection with reference: ";
        identify(*randomObject);

        delete randomObject;

    }
    std::cout << "\n-------------------" << std::endl;

    Base obj;
    
    std::cout << "Cast detection with pointer: ";
    identify(&obj);

    std::cout << "Cast detection with reference: ";
    identify(obj);

    std::cout << "\n-------------------" << std::endl;
    return 0;
}