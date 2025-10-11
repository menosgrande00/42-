#include "Cat.hpp"
#include <iostream>

Cat::Cat()
{
	type = "Cat";
	std::cout << "Cat default ctor called." << std::endl;
}

Cat::Cat(const Cat& other) : Animal(other)
{
	type = "Cat";
	std::cout << "Cat copy ctor called." << std::endl;
}

Cat &Cat::operator=(const Cat& other)
{
	if (this != &other)
	{
		Animal::operator=(other);
		type = "Cat";
	}
	std::cout << "Cat copy assignment operator called." << std::endl;
	return *this;
}

Cat::~Cat()
{
	std::cout << "Cat destructor called" << std::endl;
}

void Cat::makeSound() const
{
	std::cout << "Miyaw!" << std::endl;
}