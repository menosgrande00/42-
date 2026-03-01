#include "Bureaucrat.hpp"
#include "Form.hpp"
#include <iostream>

int main()
{
    std::cout << "--- TEST 1: Form Creation and Info ---" << std::endl;
    try
    {
        Form f1("Tax Form", 50, 20);
        std::cout << f1 << std::endl;
    }
    catch (std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    std::cout << "\n--- TEST 2: Form Invalid Grades ---" << std::endl;
    try
    {
        Form f2("Top Secret", 0, 10);
        std::cout << f2 << std::endl;
    }
    catch (std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    try
    {
        Form f3("Junk Form", 100, 151);
        std::cout << f3 << std::endl;
    }
    catch (std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    std::cout << "\n--- TEST 3: Successful Signing ---" << std::endl;
    try
    {
        Bureaucrat boss("Boss", 1);
        Form contract("Contract", 10, 5);
        
        std::cout << contract << std::endl;
        boss.signForm(contract);
        std::cout << contract << std::endl;
    }
    catch (std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    std::cout << "\n--- TEST 4: Unsuccessful Signing ---" << std::endl;
    try
    {
        Bureaucrat intern("Intern", 150);
        Form treaty("Peace Treaty", 1, 1);
        
        std::cout << treaty << std::endl;
        intern.signForm(treaty);
        std::cout << treaty << std::endl;
    }
    catch (std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
