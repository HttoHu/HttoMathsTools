#include "../include/algorithm.h"
#include <iostream>
std::vector<int> HM::split_number(int n)
{
	std::vector<int> ret;
	for (int i = 2; i < n + 1; i++)
	{
		while (n != i)
		{
			if (n%i == 0)
			{
				ret.push_back(i);
				n = n / i;
			}
			else
				break;
		}
	}
	ret.push_back(n);
	return ret;
}

std::vector<int>::iterator HM::find_ordered_vec(std::vector<int> &a, int n)
{
	int low = 0;
	int high = a.size() - 1;
	int mid;
	while (low <= high)
	{
		mid = low + ((high - low) >> 1);
		if (a[mid] > n)
		{
			high = mid - 1;
		}
		else if (a[mid] < n)
		{
			low = mid + 1;
		}
		else
		{
			return a.begin() + mid;
		}
	}
	return a.end();
}
void HM::cut_same_element(std::vector<int> &a, std::vector<int> &b)
{
	for (int i = 0; i < b.size(); i++)
	{
		auto result = find_ordered_vec(a, b[i]);
		if (result != a.end())
		{
			a.erase(result);
			b.erase(b.begin() + i);
			i--;
		}
	}
	if (a.size() == 0)
		a.push_back(1);
	if (b.size() == 0)
		b.push_back(1);
}

