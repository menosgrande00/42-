#include <iostream>
#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"

static void line(const char* title)
{
    std::cout << "\n==================== " << title << " ====================\n";
}

int main()
{
    line("PDF sample (const Animal*)");
    const Animal* meta = new Animal();
    const Animal* j = new Dog();
    const Animal* i = new Cat();

    std::cout << "Calling makeSound() via const Animal*:\n";
    i->makeSound();
    j->makeSound();
    meta->makeSound();

    delete meta;
    delete j;
    delete i;

    line("half Dog, half Cat");
    const int N = 6;
    Animal* zoo[N];
    for (int k = 0; k < N; ++k)
	{
        if (k % 2 == 0)
			zoo[k] = new Dog();
        else
			zoo[k] = new Cat();
    }
    for (int k = 0; k < N; ++k)
        zoo[k]->makeSound();
    for (int k = 0; k < N; ++k)
        delete zoo[k];

    line("Deep copy test");
    {
        Cat c1;
        Cat c2 = c1;
        Cat c3;
        c3 = c2;
    }
    line("done");
    return 0;
}
