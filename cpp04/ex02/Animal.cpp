#include "Animal.hpp"
#include <iostream>

Animal::Animal()
{
	type = "Animal";
	std::cout << "Animal default ctor called." << std::endl;
}

Animal::Animal(const Animal& other)
{
	type = other.type;
	std::cout << "Animal copy ctor called." << std::endl;
}

Animal &Animal::operator=(const Animal& other)
{
	if (this != &other)
		type = other.type;
	std::cout << "Animal copy assignment operator called." << std::endl;
	return *this;
}

Animal::~Animal()
{
	std::cout << "Animal destructor called" << std::endl;
}

std::string Animal::getType() const
{
    return type;
}
