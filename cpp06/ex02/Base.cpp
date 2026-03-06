#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <cstdlib>
#include <iostream>
#include <exception>

Base::~Base() {}

Base* generate(void)
{
    int randomValue = std::rand() % 3; 

    if (randomValue == 0)
    {
        std::cout << "A generated" << std::endl;
        return new A();
    }
    else if (randomValue == 1)
    {
        std::cout << "B generated" << std::endl;
        return new B();
    }
    else
    {
        std::cout << "C generated" << std::endl;
        return new C();
    }
}

void identify(Base* p)
{
    A* aPtr = dynamic_cast<A*>(p);
    if (aPtr != NULL)
    {
        std::cout << "A" << std::endl;
        return;
    }
    B* bPtr = dynamic_cast<B*>(p);
    if (bPtr != NULL)
    {
        std::cout << "B" << std::endl;
        return;
    }
    C* cPtr = dynamic_cast<C*>(p);
    if (cPtr != NULL)
    {
        std::cout << "C" << std::endl;
        return;
    }
    std::cout << "Unknown pointer!" << std::endl;
}

void identify(Base& p)
{
    try
    {
        A& aRef = dynamic_cast<A&>(p);
        (void)aRef; 
        std::cout << "A" << std::endl;
        return;
    } 
    catch (std::exception& e)
    {
    }
    try
    {
        B& bRef = dynamic_cast<B&>(p);
        (void)bRef;
        std::cout << "B" << std::endl;
        return;
    } 
    catch (std::exception& e)
    {
    }
    try
    {
        C& cRef = dynamic_cast<C&>(p);
        (void)cRef;
        std::cout << "C" << std::endl;
        return;
    } 
    catch (std::exception& e)
    {
    }
    std::cout << "Unknown reference!" << std::endl;
}