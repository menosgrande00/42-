#include "HumanB.hpp"
#include <iostream>

HumanB::HumanB(const std::string &name) : name(name) {}

void    HumanB::setWeapon(Weapon &w)
{
    weapon = &w;
}

void    HumanB::attack() const
{
    if (weapon)
        std::cout << name << " attacks with their " << weapon->getType() << std::endl;
    else
        std::cout << "No weapon" << std::endl;
}