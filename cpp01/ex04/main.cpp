#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

int	main(int argc, char **argv)
{
	if (argc == 4)
	{
		std::string filename = argv[1];
		std::string s1 = argv[2];
		std::string s2 = argv[3];
		if (s1.empty())
		{
			std::cerr << "s1 cannot be empty" << std::endl;
			return 1;
		}
		std::ifstream in (filename.c_str());
		if (!in)
		{
			std::cerr << "Error: cannot open input file" << std::endl;
			return 1;
		}
		std::ofstream out ((filename + ".replace").c_str());
		if (!out)
		{
			std::cerr << "Error: cannot open output file" << std::endl;
			return 1;
		}

		std::ostringstream buffer;
		buffer << in.rdbuf();
		std::string content = buffer.str();

		std::string result;
		std::size_t pos = 0;
		std::size_t found = content.find(s1, pos);
		while (found != std::string::npos) 
		{
		    result += content.substr(pos, found - pos);
		    result += s2;
		    pos = found + s1.length();
		    found = content.find(s1, pos);
		}
		result += content.substr(pos);
		out << result;
	}
	else
	{
		std::cout << "Wrong arguments" << std::endl;
		return 1;
	}
	return 0;
}