#include "Zombie.hpp"

Zombie::Zombie(const std::string &name) : name(name) {}

void    Zombie::announce() const
{
    std::cout << this->name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}

Zombie::~Zombie()
{
    std::cout << "Zombie " << this->name << " is destroyed" << std::endl;
}
