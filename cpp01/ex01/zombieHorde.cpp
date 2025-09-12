#include "Zombie.hpp"

Zombie *zombieHorde(int N, std::string name)
{
	Zombie *horde;
	int     i;

	i = 0;
	if (N <= 0)
		return (NULL);
	horde = new Zombie[N];
	while(i < N)
	{
		horde[i].setName(name);
		i++;
	}
	return (horde);
}