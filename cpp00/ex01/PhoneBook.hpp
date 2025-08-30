#include "Contact.hpp"

#include <iostream>
#include <iomanip>

class PhoneBook
{
	private:
		Contact	_contacts[8];
		int		_count;
		int		_index;
	public:
		PhoneBook();
		void	addContact(Contact c);
		void	listContact();
		void	displayContact(int i);
		int		getCount() const;
};