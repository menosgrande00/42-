#include "ClapTrap.hpp"
#include <iostream>

int main() {
    std::cout << "=== Constructors ===\n";
    ClapTrap c1;
    ClapTrap omer("omer");
    ClapTrap copy(omer);
    ClapTrap assigned;
    assigned = omer;

    std::cout << "\n=== Normal attack ===\n";
    omer.attack("TargetA");

    std::cout << "\n=== Energy exhaustion ===\n";
    for (int i = 0; i < 10; ++i)
        omer.attack("Dummy");
    omer.attack("Dummy");

    std::cout << "\n=== Taking damage (clamp) ===\n";
    copy.takeDamage(3);
    copy.takeDamage(100);
    copy.takeDamage(1);

    std::cout << "\n=== Repair behavior ===\n";
    assigned.beRepaired(5);
    for (int i = 0; i < 9; ++i)
        assigned.beRepaired(1);
    assigned.beRepaired(1);

    std::cout << "\n=== HP 0: cannot attack or repair ===\n";
    copy.attack("Anyone");
    copy.beRepaired(1);

    std::cout << "\n=== End of main ===\n";
    return 0;
}
