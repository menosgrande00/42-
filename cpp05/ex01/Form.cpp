#include "Form.hpp"
#include "Bureaucrat.hpp"

Form::Form(const std::string &name, int gradeToSign, int gradeToExecute)
    : name(name), isSigned(false), gradeToSign(gradeToSign), gradeToExecute(gradeToExecute)
{
    if (gradeToSign < 1 || gradeToExecute < 1)
    {
        throw Form::GradeTooHighException();
    }
    else if (gradeToSign > 150 || gradeToExecute > 150)
    {
        throw Form::GradeTooLowException();
    }
}

Form::Form() : name("Default Form"), isSigned(false), gradeToSign(150), gradeToExecute(150) {}

Form::Form(const Form &obj) 
    : name(obj.name), isSigned(obj.isSigned), gradeToSign(obj.gradeToSign), gradeToExecute(obj.gradeToExecute) {}

Form &Form::operator=(const Form &obj)
{
    if (this != &obj)
    {
        isSigned = obj.isSigned;
    }
    return *this;
}

Form::~Form() {}

const char* Form::GradeTooHighException::what() const throw()
{
    return "Form grade is too high!";
}

void Form::beSigned(const Bureaucrat &bureaucrat)
{
    if (bureaucrat.getGrade() > gradeToSign)
    {
        throw Form::GradeTooLowException();
    }
    isSigned = true;
}

const char* Form::GradeTooLowException::what() const throw()
{
    return "Form grade is too low!";
}

std::string Form::getName() const
{
    return name;
}

bool Form::getIsSigned() const
{
    return isSigned;
}

int Form::getGradeToSign() const
{
    return gradeToSign;
}

int Form::getGradeToExecute() const
{
    return gradeToExecute;
}

std::ostream &operator<<(std::ostream &os, const Form &obj)
{
    os << "Form Name: " << obj.getName() 
       << ", Status: " << (obj.getIsSigned() ? "Signed" : "Not Signed")
       << ", Grade required to sign: " << obj.getGradeToSign()
       << ", Grade required to execute: " << obj.getGradeToExecute();
    return os;
}