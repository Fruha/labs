#pragma once
namespace laba3 
{
	template <typename T>
	T get_num(const char* msg)
	{
		std::cout << msg;
		T element;

		while (!(std::cin >> element))
		{
			std::cin.clear();
			std::cin.ignore(32767, '\n');

			std::cout << "Error! Enter int!" << std::endl << msg;
		}

		std::cin.ignore(32767, '\n');

		return element;
	}
}
