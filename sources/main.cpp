#include <iostream>
#include <Windows.h>
#include "../include/basic_number.h"
#include "../include/algorithm.h"
template<typename T>
void print_vec(std::vector<T> v)
{
	for (auto a : v)
	{
		std::cout << a << " ";
	}
}
int main()
{
	HM::Fraction a(-33, -32);
	std::cout<<(a.Convert(HM::TReal))->to_string();
	//std::cout<<a.to_string();
	Sleep(100000);
	return 0;
}