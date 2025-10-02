#include "ScavTrap.hpp"
#include <iostream>

ScavTrap::ScavTrap()
{
	_hit = 100;
	_energy = 50;
	_attack = 20;
	std::cout << "ScavTrap default constructor called\n";
}

ScavTrap::ScavTrap(const std::string& name) : ClapTrap(name)
{
    _hit = 100;
    _energy = 50;
    _attack = 20;
    std::cout << "ScavTrap named constructor called\n";
}

ScavTrap::ScavTrap(const ScavTrap &other) : ClapTrap(other)
{
	std::cout << "ScavTrap copy constructor called\n";
}

ScavTrap& ScavTrap::operator=(const ScavTrap& other)
{
    if (this != &other)
        ClapTrap::operator=(other);
	std::cout << "ScavTrap copy-assigned\n";
    return *this;
}

ScavTrap::~ScavTrap()
{
	std::cout << "ScavTrap destructor called\n";
}

void    ScavTrap::attack(const std::string &target)
{
	if (_energy > 0 && _hit > 0)
	{
		std::cout << "ScavTrap " << _name << " attacks " << target << ", causing " << _attack << " points of damage!\n";
		_energy--;
	}
	else
		if (_hit <= 0)
			std::cout << "It has no hit points\n";
		else if (_energy <= 0)
			std::cout << "It has no energy\n";
}

void	ScavTrap::guardGate()
{
	std::cout << "ScavTrap " << _name << " is now in Gate keeper mode\n";
}