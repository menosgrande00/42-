#include "Bureaucrat.hpp"

//******************************************************************************************//

Bureaucrat::Bureaucrat() : name("Default"), grade(150) {}

Bureaucrat::Bureaucrat(const std::string &name, int grade) : name(name)
{
	if (grade < 1)
	{
		throw Bureaucrat::GradeTooHighException();
	}
	else if (grade > 150)
	{
		throw Bureaucrat::GradeTooLowException();
	}
	this->grade = grade;
}

Bureaucrat::Bureaucrat(const Bureaucrat &obj) : name(obj.name), grade(obj.grade) {}

Bureaucrat &Bureaucrat::operator=(const Bureaucrat &obj)
{
	if (this != &obj)
	{
		grade = obj.grade;
	}
	return *this;
}

Bureaucrat::~Bureaucrat() {}

//******************************************************************************************//

void Bureaucrat::incrementGrade()
{
	if (grade - 1 < 1)
	{
		throw Bureaucrat::GradeTooHighException();
	}
	grade--;
}

void Bureaucrat::decrementGrade()
{
	if (grade + 1 > 150)
	{
		throw Bureaucrat::GradeTooLowException();
	}
	grade++;
}

std::ostream &operator<<(std::ostream &os, const Bureaucrat &obj)
{
	os << obj.getName() << ", bureaucrat grade " << obj.getGrade() << ".";
	return os;
}

//******************************************************************************************//

const char *Bureaucrat::GradeTooHighException::what() const throw()
{
	return "Grade is too high! Maximum grade is 1";
}

const char *Bureaucrat::GradeTooLowException::what() const throw()
{
	return "Grade is too low! Minimum grade is 150";
}

//******************************************************************************************//

std::string Bureaucrat::getName() const
{
	return name;
}

int Bureaucrat::getGrade() const
{
	return grade;
}

