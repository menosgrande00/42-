#include "Contact.hpp"

std::string Contact::getFirstName() const
{
	return _firstName;
}
std::string Contact::getLastName() const
{
	return _lastName;
}
std::string Contact::getNickName() const
{
	return _nickName;
}
std::string Contact::getDarkSecret() const
{
	return _dark;
}
std::string Contact::getPhoneNumber() const
{
	return _phoneNumber;
}

void	Contact::setContact(std::string f,
							std::string l,
							std::string n,
							std::string d,
							std::string p)
{
    _firstName = f;
    _lastName = l;
    _nickName = n;
    _dark = d;
    _phoneNumber = p;
}

void	Contact::display() const
{
	std::cout << "First Name: " << getFirstName() << std::endl;
	std::cout << "Last Name: " << getLastName() << std::endl;
	std::cout << "Nickname: " << getNickName() << std::endl;
	std::cout << "Phone Number: " << getPhoneNumber() << std::endl;
	std::cout << "Dark Secret: " << getDarkSecret() << std::endl;
}