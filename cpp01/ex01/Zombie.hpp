#ifndef ZOMBIE_HPP
# define ZOMBIE_HPP

#include <string>
#include <iostream>

class	Zombie
{
	private:
		std::string name;
	public:
		Zombie();
		Zombie(const std::string& n);
		~Zombie();

		void		setName(const std::string &n);
		void		announce() const;
};

#endif