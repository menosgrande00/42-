#include "Zombie.hpp"

Zombie* zombieHorde(int N, std::string name);

int main()
{
    int     i = 0;
//////////////////////////////////////////////////////
    std::cout << "--- 5 zombies ---" << std::endl;
    Zombie  *horde = zombieHorde(5, "Omer");
    while(i < 5)
    {
        horde[i].announce();
        i++;
    }
    delete[] horde;
//////////////////////////////////////////////////////
    std::cout << "--- 1 zombie ---" << std::endl;
    Zombie* single = zombieHorde(1, "faruk");
    single[0].announce();
    delete[] single;
//////////////////////////////////////////////////////
    std::cout << "--- 0 zombies ---" << std::endl;
    Zombie* none = zombieHorde(0, "Baz");
    if (!none) {
        std::cout << "Horde is NULL" << std::endl;
    }
//////////////////////////////////////////////////////
    return 0;
}