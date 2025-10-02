#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include <iostream>

int main()
{
	int i = 0;

	ClapTrap a("a");
	ScavTrap b("b");

	std::cout << "\n-------------------\n\n";

	b.attack("innocent");
	b.guardGate();

	std::cout << "\n-------------------\n\n";

	ScavTrap copy(b);
	ScavTrap assigned;
	assigned = b;

	copy.attack("s1");
	assigned.attack("s2");

	std::cout << "\n-------------------\n\n";

	while(i < 55)
	{
		b.attack("innocent");
		i++;
	}

	std::cout << "\n-------------------\n\n";
	b.attack("innocent");
	a.attack("innocent");
}
