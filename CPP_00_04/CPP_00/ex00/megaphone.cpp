#include <iostream>

int	main(int ac, char **av)
{
	if (ac == 1)
	{
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
		return (0);
	}

	for (int i = 1; i < ac; i++)
	{
		std::string str = av[i];
		for (std::size_t j = 0; j < str.length(); j++)
			std::cout << static_cast<char>(std::toupper(static_cast<unsigned char>(str[j])));
		std::cout << ' ';
	}
	std::cout << std::endl;

	return (0);
}