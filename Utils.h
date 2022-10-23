#pragma once
#include<iostream>

template <typename T>

T InputCheck(T min, T max)
{
	T x{};
	while ((std::cin >> x).fail() || (x < min) || (x > max))
	{
		std::cin.clear();
		std::cin.ignore(10000, '\n');
		std::cout << "попробуйте еще раз" << std::endl;
	}
	return x;
}