#pragma once
#include <vector>
namespace HM
{
	std::vector<int> split_number(int n);
	void cut_same_element(std::vector<int> &a, std::vector<int> &b);
	std::vector<int>::iterator find_ordered_vec(std::vector<int> &a, int n);
}