#include "Fixed.hpp"
#include <cmath>

const int Fixed::_constbit8 = 8;

Fixed&       Fixed::min(Fixed& a, Fixed& b)
{
	if (a < b)
		return a;
	else
		return b;
}
Fixed const& Fixed::min(Fixed const& a, Fixed const& b)
{
	if (a < b)
		return a;
	else
		return b;
}
Fixed&       Fixed::max(Fixed& a, Fixed& b)
{
	if (a > b)
		return a;
	else
		return b;
}
Fixed const& Fixed::max(Fixed const& a, Fixed const& b)
{
	if (a > b)
		return a;
	else
		return b;
}

Fixed& Fixed::operator++()
{
    ++_raw;
    return *this;
}

Fixed Fixed::operator++(int)
{
    Fixed tmp(*this);
    ++_raw;
    return tmp;
}

Fixed& Fixed::operator--()
{
    --_raw;
    return *this;
}

Fixed Fixed::operator--(int)
{
    Fixed tmp(*this);
    --_raw;
    return tmp;
}

Fixed Fixed::operator/(Fixed const& rhs) const
{
    Fixed out;
    if (rhs._raw == 0)
		return out;
    long tmp = (static_cast<long>(_raw) << _constbit8) / static_cast<long>(rhs._raw);
    out.setRawBits(static_cast<int>(tmp));
    return out;
}

Fixed Fixed::operator*(Fixed const& rhs) const
{
    Fixed out;
    long tmp = static_cast<long>(_raw) * static_cast<long>(rhs._raw);
    out.setRawBits(static_cast<int>(tmp >> _constbit8));
    return out;
}

Fixed Fixed::operator+(Fixed const& rhs) const
{
    Fixed out;
    out.setRawBits(_raw + rhs._raw);
    return out;
}

Fixed Fixed::operator-(Fixed const& rhs) const
{
    Fixed out;
    out.setRawBits(_raw - rhs._raw);
    return out;
}

bool Fixed::operator<(Fixed const& rhs) const
{
	return _raw < rhs._raw;
}

bool Fixed::operator>(Fixed const& rhs) const
{
	return _raw > rhs._raw;
}

bool Fixed::operator<=(Fixed const& rhs) const
{
	return _raw <= rhs._raw;
}

bool Fixed::operator>=(Fixed const& rhs) const
{
	return _raw >= rhs._raw;
}

bool Fixed::operator==(Fixed const& rhs) const
{
	return _raw == rhs._raw;
}

bool Fixed::operator!=(Fixed const& rhs) const
{
	return _raw != rhs._raw;
}

//--------------------------------------

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

//-------------------------------------

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