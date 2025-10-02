#include "FragTrap.hpp"
#include <iostream>

FragTrap::FragTrap()
{
	_hit = 100;
	_energy = 100;
	_attack = 30;
	std::cout << "FragTrap default constructor called\n";
}

FragTrap::FragTrap(const std::string &name) : ClapTrap(name)
{
    _hit = 100;
    _energy = 50;
    _attack = 20;
    std::cout << "FragTrap named constructor called\n";
}

FragTrap::FragTrap(const FragTrap &other) : ClapTrap(other)
{
	std::cout << "FragTrap copy constructor called\n";
}

FragTrap& FragTrap::operator=(const FragTrap& other)
{
    if (this != &other)
        ClapTrap::operator=(other);
    std::cout << "FragTrap copy-assigned\n";
    return *this;
}

FragTrap::~FragTrap()
{
	std::cout << "FragTrap destructor called\n";
}

void	FragTrap::highFivesGuys(void)
{
	std::cout << "FragTrap " << _name << " requests a positive high five!\n";
}