#include "Contact.hpp"
#include "PhoneBook.hpp"

bool	isNumber(const std::string &s)
{
	size_t	i;

	i = 0;
	if (s.empty())
		return (false);
	while (i < s.size())
	{
		if (!isdigit(s[i]))
			return (false);
		i++;
	}
	return (true);
}

int	main()
{
	PhoneBook	pb;
	std::string	str;
	std::string	input;
	std::string first, last, nick, dark, phone;
	int			i;

	while (1)
	{
		std::cout << "3 options: ADD,SEARCH,EXIT" << std::endl;
		std::cout << ">";
		std::cin >> str;
		if (str == "SEARCH")
		{
			if (pb.getCount() == 0)
				std::cout << "PhoneBook is empty!" << std::endl;
			else
			{
				pb.listContact();
				std::cout << "Enter an index: ";
				std::cin >> input;
				if (!isNumber(input)) 
				{
    				std::cout << "Invalid index" << std::endl;
    				continue;
				}
				i = std::atoi(input.c_str());
				pb.displayContact(i);
			}
		}
		else if (str == "ADD")
		{
			std::cout << "First Name: ";
			std::cin >> first;

			std::cout << "Last Name: ";
			std::cin >> last;

			std::cout << "Nickname: ";
			std::cin >> nick;

			std::cout << "Dark Secret: ";
			std::cin >> dark;

			std::cout << "Phone Number: ";
			std::cin >> phone;

			Contact		c;
			c.setContact(first, last, nick, phone, dark);
			pb.addContact(c);
			std::cout << "Contact added!" << std::endl;
		}
		else if (str == "EXIT")
		{
			std::cout << "exit" << std::endl;
			break ;
		}
		else
			continue ;
	}
	return (0);
}