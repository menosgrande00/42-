#include "Zombie.hpp"

Zombie* newZombie(std::string name);
void randomChump(std::string name);

int main()
{
    std::cout << "--- stack test ---" << std::endl;
    randomChump("Omer");

    std::cout << "--- heap test ---" << std::endl;
    Zombie* z1 = newZombie("Faruk");
    z1->announce();
    delete z1;

    std::cout << "--- multiple heap test ---" << std::endl;
    Zombie* z2 = newZombie("Omer");
    Zombie* z3 = newZombie("Faruk");
    z2->announce();
    z3->announce();
    delete z2;
    delete z3;

    return 0;
}
