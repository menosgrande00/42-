#include "PhoneBook.hpp"

PhoneBook::PhoneBook()
{
	_count = 0;
	_index = 0;
}

int		PhoneBook::getCount() const
{
	return _count;
}

void	PhoneBook::addContact(Contact c)
{
	_contacts[_index] = c;
	_index = (_index + 1) % 8;
	if (_count < 8)
		_count++;
}

std::string truncate(std::string str) 
{
    if (str.length() > 10)
        return str.substr(0, 9) + ".";
    return (str);
}

void	PhoneBook::listContact()
{
	int	i;

	i = 0;

	std::cout << std::setw(10) << std::right << "Index" << "|"
      << std::setw(10) << std::right << "First Name" << "|"
      << std::setw(10) << std::right << "Last Name" << "|"
      << std::setw(10) << std::right << "Nickname" << std::endl;

	std::cout << std::string(44, '-') << std::endl;

	while(i < _count)
	{
		std::cout	<< std::setw(10) << std::right
						<< i << "|"
					<< std::setw(10) << std::right
						<< truncate(_contacts[i].getFirstName()) << "|"
					<< std::setw(10) << std::right
						<< truncate(_contacts[i].getLastName()) << "|"
					<< std::setw(10) << std::right
						<< truncate(_contacts[i].getNickName())
					<< std::endl;
		i++;
	}
}
void	PhoneBook::displayContact(int i)
{
	if (i < 0 || i >= _count)
	{
		std::cout << "Wrong index! Please enter a number between 0 and " 
        	<< _count - 1 << std::endl;
		return ;
	}
	_contacts[i].display();
}
