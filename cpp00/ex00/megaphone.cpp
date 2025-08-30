#include <iostream>

int main(int argc, char **argv)
{
	int i = 1;
	int j = 0;

	if (argc == 1)
	{
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
		return (0);
	}
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			argv[i][j] = std::toupper(argv[i][j]);
			std::cout << argv[i][j];
			j++;
		}
		if (i < argc - 1)
			std::cout << " ";
		i++;
	}
	std::cout << std::endl;
	return (0);
}
