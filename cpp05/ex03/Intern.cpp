#include "Intern.hpp"

Intern::Intern() {}

Intern::Intern(const Intern &obj) 
{
    (void)obj;
}

Intern &Intern::operator=(const Intern &obj)
{
    (void)obj;
    return *this;
}

Intern::~Intern() {}

const char* Intern::FormNotFoundException::what() const throw()
{
    return "Intern is confused! The requested form name does not exist.";
}

AForm *Intern::makeForm(const std::string &formName, const std::string &target)
{
    std::string formNames[] = {
        "shrubbery creation",
        "robotomy request",
        "presidential pardon"
    };

    int i = 0;
    while (i < 3)
    {
        if (formName == formNames[i])
        {
            break;
        }
        i++;
    }
    AForm *createdForm = NULL;
    switch (i)
    {
        case 0:
            createdForm = new ShrubberyCreationForm(target);
            break;
        case 1:
            createdForm = new RobotomyRequestForm(target);
            break;
        case 2:
            createdForm = new PresidentialPardonForm(target);
            break;
        default:
            std::cout << "Error: Intern couldn't find the form '" << formName << "'!" << std::endl;
            return NULL; 
    }
    std::cout << "Intern creates " << createdForm->getName() << std::endl;

    return createdForm;
}