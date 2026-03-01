#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

int main()
{
    srand(time(NULL));

    std::cout << "--- CREATING BUREAUCRATS ---" << std::endl;
    Bureaucrat boss("Boss", 1);
    Bureaucrat midTier("MidTier", 50);
    Bureaucrat intern("Intern", 150);

    std::cout << boss << "\n" << midTier << "\n" << intern << std::endl;

    std::cout << "\n--- CREATING FORMS ---" << std::endl;
    ShrubberyCreationForm shrub("Bahce");
    RobotomyRequestForm robot("Arcelik");
    PresidentialPardonForm pardon("KASET CALAR");

    std::cout << "\n--- TEST 1: EXECUTING UNSIGNED FORM ---" << std::endl;
    boss.executeForm(shrub);

    std::cout << "\n--- TEST 2: SHRUBBERY CREATION FORM ---" << std::endl;
    intern.signForm(shrub);
    midTier.signForm(shrub);
    intern.executeForm(shrub);
    midTier.executeForm(shrub);

    std::cout << "\n--- TEST 3: ROBOTOMY REQUEST FORM ---" << std::endl;
    midTier.signForm(robot);
    midTier.executeForm(robot);
    boss.executeForm(robot);
    boss.executeForm(robot);

    std::cout << "\n--- TEST 4: PRESIDENTIAL PARDON FORM ---" << std::endl;
    midTier.signForm(pardon);
    boss.signForm(pardon);
    boss.executeForm(pardon);

    std::cout << "\n--- TESTS COMPLETED ---" << std::endl;

    return 0;
}