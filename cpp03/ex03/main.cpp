#include "DiamondTrap.hpp"
#include <iostream>

int main()
{
	DiamondTrap a("omer");
	DiamondTrap b(a);
	DiamondTrap c;

	c = a;
	int i = 55;

	a.takeDamage(99);
	a.beRepaired(51);
	a.beRepaired(50);
	while (i-- >= 0)
		b.attack("you");
	a.guardGate();
	a.highFivesGuys();
	a.whoAmI();
}
