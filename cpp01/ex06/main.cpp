#include "Harl.hpp"
#include <string>
#include <iostream>

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Usage: ./harlFilter <DEBUG | INFO | WARNING | ERROR>" << std::endl;
		return 1;
	}

	const std::string level = argv[1];
	int	i = -1;
	Harl harl;

	if (level == "DEBUG")
		i = 0;
	else if (level == "INFO")
		i = 1;
	else if (level == "WARNING")
		i = 2;
	else if (level == "ERROR")
		i = 3;

	switch (i) 
	{
	  case 0:
	    std::cout << "[ DEBUG ]\n";
	    harl.complain("DEBUG");

	  case 1:
	    std::cout << "[ INFO ]\n";
	    harl.complain("INFO");

	  case 2:
	    std::cout << "[ WARNING ]\n";
	    harl.complain("WARNING");

	  case 3:
	    std::cout << "[ ERROR ]\n";
	    harl.complain("ERROR");
	    break;

	  default:
	    std::cout << "[ Probably complaining about insignificant problems ]\n";
	}
	return 0;
}