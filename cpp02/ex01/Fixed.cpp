#include "Fixed.hpp"
#include <cmath>

const int Fixed::_constbit8 = 8;

Fixed::Fixed(int n)
{
	std::cout << "Int constructor called" << std::endl;
	_raw = n << _constbit8;
}

Fixed::Fixed(float f)
{
	std::cout << "Float constructor called" << std::endl;
	_raw = static_cast<int>(roundf(f * (1 << _constbit8)));
}

float Fixed::toFloat() const
{
	return static_cast<float>(_raw) / (1 << _constbit8);
}

int Fixed::toInt() const
{
	return _raw >> _constbit8;
}

std::ostream& operator<<(std::ostream& os, Fixed const& x)
{
	return os << x.toFloat();
}

Fixed::Fixed()
{
	_raw = 0;
	std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(Fixed const &other)
{
	std::cout << "Copy constructor called" << std::endl;
	*this = other;
}

Fixed& Fixed::operator=(Fixed const& other)
{
	std::cout << "Copy assignment operator called" << std::endl;
	if (this != &other) 
		this->_raw = other._raw;
	return *this;
}

Fixed::~Fixed() 
{
	std::cout << "Destructor called" << std::endl;
}

int Fixed::getRawBits(void) const 
{
	std::cout << "getRawBits member function called" << std::endl;
	return this->_raw;
}

void Fixed::setRawBits(int const raw) 
{
	this->_raw = raw;
}