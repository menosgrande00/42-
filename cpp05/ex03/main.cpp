#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "Intern.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

int main()
{
    srand(time(NULL));

    std::cout << "--- CREATING INTERN AND BUREAUCRAT ---" << std::endl;
    Intern someRandomIntern;
    Bureaucrat boss("Boss", 1);

    AForm* form1;
    AForm* form2;
    AForm* form3;
    AForm* form4;

    std::cout << "\n--- TEST 1: ROBOTOMY REQUEST ---" << std::endl;
    form1 = someRandomIntern.makeForm("robotomy request", "Bender");
    if (form1)
    {
        boss.signForm(*form1);
        boss.executeForm(*form1);
        delete form1;
    }

    std::cout << "\n--- TEST 2: SHRUBBERY CREATION ---" << std::endl;
    form2 = someRandomIntern.makeForm("shrubbery creation", "Garden");
    if (form2)
    {
        boss.signForm(*form2);
        boss.executeForm(*form2);
        delete form2;
    }

    std::cout << "\n--- TEST 3: PRESIDENTIAL PARDON ---" << std::endl;
    form3 = someRandomIntern.makeForm("presidential pardon", "Arthur Dent");
    if (form3)
    {
        boss.signForm(*form3);
        boss.executeForm(*form3);
        delete form3;
    }

    std::cout << "\n--- TEST 4: INVALID FORM ---" << std::endl;
    form4 = someRandomIntern.makeForm("time travel request", "DeLorean");
    if (form4)
    {
        boss.signForm(*form4);
        boss.executeForm(*form4);
        delete form4;
    }

    std::cout << "\n--- TESTS COMPLETED ---" << std::endl;

    return 0;
}