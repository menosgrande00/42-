#include "ClapTrap.hpp"
#include <iostream>

ClapTrap::ClapTrap() : _hit(10), _energy(10), _attack(0)
{
	std::cout << "Default constructor called\n";
}

ClapTrap::ClapTrap(const std::string &name) : _name(name), _hit(10), _energy(10), _attack(0)
{
	std::cout << "Named constructor called\n";
}

ClapTrap::ClapTrap(const ClapTrap& other)
{
	std::cout << "Copy constructor called\n";
	*this = other;
}

ClapTrap &ClapTrap::operator=(const ClapTrap &other)
{
	std::cout << "Copy assignment operator called\n";
	if (this != &other)
	{
		this->_attack = other._attack;
		this->_energy = other._energy;
		this->_hit = other._hit;
		this->_name = other._name;
	}
	return *this;
}

ClapTrap::~ClapTrap()
{
	std::cout << "Destructor called\n";
}

void    ClapTrap::attack(const std::string &target)
{
	if (_energy > 0 && _hit > 0)
	{
		std::cout << "ClapTrap " << _name << " attacks " << target << ", causing " << _attack << " points of damage!\n";
		_energy--;
	}
	else
		if (_hit <= 0)
			std::cout << "It has no hit points\n";
		else if (_energy <= 0)
			std::cout << "It has no energy\n";
}

void	ClapTrap::beRepaired(unsigned int amount)
{
	if (_energy > 0 && _hit > 0)
	{
		std::cout << "ClapTrap " << _name << " regenered " << amount << " hit point\n";
		_energy--;
		_hit = _hit + amount;
	}
	else
		if (_hit <= 0)
			std::cout << "It has no hit points\n";
		else if (_energy <= 0)
			std::cout << "It has no energy\n";
}

void	ClapTrap::takeDamage(unsigned int amount)
{
	if (_hit > 0)
	{
		std::cout << "ClapTrap " << _name << " took " << amount << " damage\n";
		if (amount >= _hit)
			_hit = 0;
		else
			_hit = _hit - amount;
	}
	else
		if (_hit == 0)
			std::cout << "It has no hit points\n";
}
