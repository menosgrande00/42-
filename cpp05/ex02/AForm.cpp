#include "AForm.hpp"
#include "Bureaucrat.hpp"

AForm::AForm(const std::string &name, int gradeToSign, int gradeToExecute)
    : name(name), isSigned(false), gradeToSign(gradeToSign), gradeToExecute(gradeToExecute)
{
    if (gradeToSign < 1 || gradeToExecute < 1)
    {
        throw AForm::GradeTooHighException();
    }
    else if (gradeToSign > 150 || gradeToExecute > 150)
    {
        throw AForm::GradeTooLowException();
    }
}

AForm::AForm() : name("Default AForm"), isSigned(false), gradeToSign(150), gradeToExecute(150) {}

AForm::AForm(const AForm &obj) 
    : name(obj.name), isSigned(obj.isSigned), gradeToSign(obj.gradeToSign), gradeToExecute(obj.gradeToExecute) {}

AForm &AForm::operator=(const AForm &obj)
{
    if (this != &obj)
    {
        isSigned = obj.isSigned;
    }
    return *this;
}

AForm::~AForm() {}

const char* AForm::GradeTooHighException::what() const throw()
{
    return "AForm grade is too high!";
}

void AForm::beSigned(const Bureaucrat &bureaucrat)
{
    if (bureaucrat.getGrade() > gradeToSign)
    {
        throw AForm::GradeTooLowException();
    }
    isSigned = true;
}

void AForm::checkExecution(Bureaucrat const & executor) const
{
    if (!isSigned)
    {
        throw AForm::NotSignedException();
    }
        if (executor.getGrade() > this->gradeToExecute)
    {
        throw AForm::GradeTooLowException();
    }
}

const char* AForm::GradeTooLowException::what() const throw()
{
    return "AForm grade is too low!";
}

const char* AForm::NotSignedException::what() const throw()
{
    return "Form cannot be executed because it is not signed!";
}

std::string AForm::getName() const
{
    return name;
}

bool AForm::getIsSigned() const
{
    return isSigned;
}

int AForm::getGradeToSign() const
{
    return gradeToSign;
}

int AForm::getGradeToExecute() const
{
    return gradeToExecute;
}

std::ostream &operator<<(std::ostream &os, const AForm &obj)
{
    os << "AForm Name: " << obj.getName() 
       << ", Status: " << (obj.getIsSigned() ? "Signed" : "Not Signed")
       << ", Grade required to sign: " << obj.getGradeToSign()
       << ", Grade required to execute: " << obj.getGradeToExecute();
    return os;
}