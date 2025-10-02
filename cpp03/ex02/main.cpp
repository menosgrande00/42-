#include "ClapTrap.hpp"
#include "FragTrap.hpp"
#include <iostream>

int main()
{
	int i = 0;

	ClapTrap a("a");
	FragTrap b("b");

	std::cout << "\n-------------------\n\n";

	b.attack("innocent");
	b.highFivesGuys();

	std::cout << "\n-------------------\n\n";

	FragTrap copy(b);
	FragTrap assigned;
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
