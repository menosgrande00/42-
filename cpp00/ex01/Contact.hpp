#ifndef CONTACT_HPP
# define CONTACT_HPP

#include <iostream>

class Contact
{
	private:
		std::string	_firstName;
		std::string	_lastName;
		std::string	_nickName;
		std::string	_dark;
		std::string	_phoneNumber;

	public:
		std::string getFirstName() const;
		std::string	getLastName() const;
		std::string	getNickName() const;
		std::string	getDarkSecret() const;
		std::string	getPhoneNumber() const;

		void setContact(std::string f,
							std::string l,
							std::string n,
							std::string d,
							std::string p);

		void display() const;
};

#endif