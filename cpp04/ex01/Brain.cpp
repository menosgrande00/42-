#include "Brain.hpp"
#include <iostream>

Brain::Brain()
{
	int i = -1;
	while (++i < 100)
		ideas[i] = "";
	std::cout << "Brain default ctor called." << std::endl;
}

Brain::Brain(const Brain &other)
{
	int i = -1;
	while(++i < 100)
		ideas[i] = other.ideas[i];
	std::cout << "Brain copy ctor called." << std::endl;
}

Brain& Brain::operator=(const Brain& other)
{
	if (this != &other)
	{
		int i = -1;
		while(++i < 100)
			ideas[i] = other.ideas[i];
	}
	std::cout << "Brain copy assignment operator called." << std::endl;
	return *this;
}

Brain::~Brain()
{
    std::cout << "Brain destructor called." << std::endl;
}