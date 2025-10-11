#include "Dog.hpp"
#include <iostream>

Dog::Dog()
{
	type = "Dog";
	std::cout << "Dog default ctor called." << std::endl;
}

Dog::Dog(const Dog& other) : Animal(other)
{
	type = "Dog";
	std::cout << "Dog copy ctor called." << std::endl;
}

Dog &Dog::operator=(const Dog& other)
{
	if (this != &other)
	{
		Animal::operator=(other);
		type = "Dog";
	}
	std::cout << "Dog copy assignment operator called." << std::endl;
	return *this;
}

Dog::~Dog()
{
	std::cout << "Dog destructor called" << std::endl;
}

void Dog::makeSound() const
{
	std::cout << "Woof Woof!" << std::endl;
}