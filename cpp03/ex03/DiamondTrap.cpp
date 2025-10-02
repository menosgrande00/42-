#include "DiamondTrap.hpp"
#include <iostream>

DiamondTrap::DiamondTrap()
	:	ClapTrap("_clap_name"),
		ScavTrap(),
		FragTrap(),
		_name()
{
	_hit = 100;
	_energy = 50;
	_attack = 30;
	std::cout << "DiamondTrap default constructor called\n";
}

DiamondTrap::DiamondTrap(const std::string &name)
	:   ClapTrap(name + "_clap_name"),
		ScavTrap(name),
		FragTrap(name),
		_name(name)
{
	_hit = 100;
	_energy = 50;
	_attack = 30;
	std::cout << "DiamondTrap named constructor called\n";
}

DiamondTrap::DiamondTrap(const DiamondTrap &other)
	:	ClapTrap(other),
		ScavTrap(other),
		FragTrap(other),
		_name(other._name)
{
	std::cout << "DiamondTrap copy constructor called\n";
}

DiamondTrap& DiamondTrap::operator=(const DiamondTrap& other)
{
	if (this != &other)
		ClapTrap::operator=(other);
		ScavTrap::operator=(other);
		FragTrap::operator=(other);

		_name = other._name;
		_hit = other._hit;
		_energy = other._energy;
		_attack = other._attack;
	std::cout << "DiamondTrap copy-assigned\n";
	return *this;
}

DiamondTrap::~DiamondTrap()
{
	std::cout << "DiamondTrap destructor called\n";
}

void	DiamondTrap::whoAmI(void)
{
	std::cout << "I am " << _name << " and my ClapTrap name is "
	<< ClapTrap::_name << std::endl;
}