#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>

class Fixed
{
	private:
		int					_raw;
		static const int	_constbit8;
	public:
		Fixed();
		Fixed(Fixed const &other);
		Fixed &operator=(Fixed const &other);
		~Fixed();

		int		getRawBits(void) const;
		void	setRawBits(int const raw);

		Fixed(int n);
		Fixed(float f);

		float toFloat(void) const;
		int toInt(void)		const;
};

std::ostream& operator<<(std::ostream& os, Fixed const& x);

#endif