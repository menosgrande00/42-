#ifndef INTERN_HPP
#define INTERN_HPP

#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <string>
#include <iostream>

class Intern
{
    public:
        Intern();
        Intern(const Intern &obj);
        Intern &operator=(const Intern &obj);
        ~Intern();

        AForm *makeForm(const std::string &formName, const std::string &target);
        
        class FormNotFoundException : public std::exception
        {
            public:
                virtual const char* what() const throw();
        };
};

#endif