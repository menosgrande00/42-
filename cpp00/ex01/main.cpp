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
		std::getline(std::cin, str);
		if (std::cin.eof())
			exit(0);
		if (str == "SEARCH")
		{
			if (pb.getCount() == 0)
				std::cout << "PhoneBook is empty!" << std::endl;
			else
			{
				pb.listContact();
				std::cout << "Enter an index: ";
				std::getline(std::cin, input);
				if (std::cin.eof())
					exit(0);
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
			std::getline(std::cin, first);
			if (std::cin.eof())
				exit(0);
			if (first.empty())
			{
				std::cout << "First Name cannot be empty" << std::endl;
				continue ;
			}
			std::cout << "Last Name: ";
			std::getline(std::cin, last);
			if (std::cin.eof())
				exit(0);
			if (last.empty())
			{
				std::cout << "Last Name cannot be empty" << std::endl;
				continue ;
			}
			std::cout << "Nickname: ";
			std::getline(std::cin, nick);
			if (std::cin.eof())
				exit(0);
			if (nick.empty())
			{
				std::cout << "Nickname cannot be empty" << std::endl;
				continue ;
			}
			std::cout << "Dark Secret: ";
			std::getline(std::cin, dark);
			if (std::cin.eof())
				exit(0);
			if (dark.empty())
			{
				std::cout << "Dark Secret cannot be empty" << std::endl;
				continue ;
			}
			std::cout << "Phone Number: ";
			std::getline(std::cin, phone);
			if (std::cin.eof())
				exit(0);
			if (phone.empty())
			{
				std::cout << "Phone Number cannot be empty" << std::endl;
				continue ;
			}
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
