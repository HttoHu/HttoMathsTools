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
	HM::SReal tmp= std::make_shared<HM::Real>(1.75);
	HM::SFraction obj = std::make_shared<HM::Fraction>(1,4324);
	std::cout << obj->operate(HM::PLUS, tmp)->to_string();
	Sleep(100000);
	return 0;
}