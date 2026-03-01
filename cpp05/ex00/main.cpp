#include "Bureaucrat.hpp"

int main() 
{
    std::cout << "\n--- TEST 1: Valid Bureaucrat ---\n" << std::endl;
    try 
    {
        Bureaucrat b1("John", 50);
        std::cout << b1 << std::endl;
        
        b1.incrementGrade();
        std::cout << "After promotion: " << b1 << std::endl;
    } 
    catch (std::exception &e) 
    {
        std::cerr << "Caught exception: " << e.what() << std::endl;
    }

    std::cout << "\n--- TEST 2: Grade Too High ---\n" << std::endl;
    try 
    {
        Bureaucrat b2("Boss", 0);
        std::cout << b2 << std::endl; 
    } 
    catch (std::exception &e) 
    {
        std::cerr << "Caught exception: " << e.what() << std::endl;
    }

    std::cout << "\n--- TEST 3: Out of Bounds Decrement ---\n" << std::endl;
    try 
    {
        Bureaucrat b3("Intern", 150);
        std::cout << b3 << std::endl;
        
        b3.decrementGrade(); 
    } 
    catch (std::exception &e) 
    {
        std::cerr << "Caught exception: " << e.what() << std::endl;
    }

    return 0;
}