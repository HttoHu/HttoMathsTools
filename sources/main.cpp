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
	try
	{
		HM::SSurd tmp2 = std::make_shared<HM::Surd>(-1, 8);
		HM::SSurd tmp = std::make_shared<HM::Surd>(3, 7);
		HM::SurdBunch sb({ tmp2,tmp,tmp,tmp2});
		std::cout << sb.operate(HM::PLUS, tmp)->to_string();
		sb.simplify();
		//std::cout << sb.to_string();
		Sleep(100000);
	}
	catch (std::exception &e)
	{
		std::cout << e.what();
	}
	return 0;
}