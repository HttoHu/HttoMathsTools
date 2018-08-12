#include "../include/basic_number.h"
#include "../include/algorithm.h";
using namespace HM;
#define SNEW std::make_shared
bool isEqual(int n, float f)
{
	if ((float)n == f)
		return true;
	else
		return false;
}

SBasic HM::Fraction::operate(Operator, SBasic &)
{
	return SBasic();
}
SBasic HM::Fraction::simplify()
{
	std::vector<int> num_vec = split_number(std::abs(num));
	std::vector<int> den_vec = split_number(std::abs(den));
	cut_same_element(num_vec, den_vec);
	num = num/std::abs(num);
	for (auto a : num_vec)
	{
		num *= a;
	}
	den = den / std::abs(den);
	if (num < 0 && den < 0)
	{ 
		num = -num;
		den = -den;
	}
	else if (den < 0)
	{
		den = -den;
		num = -num;
	}
	for (auto a : den_vec)
	{
		den *= a;
	}
	return SNEW<Fraction>(num, den);
}
std::string HM::Fraction::to_string()
{
	if (den == 1)
		return std::to_string(num);
	return std::to_string(num) + "/" + std::to_string(den);
}
SBasic HM::Fraction::Convert(ObjType objt)
{
	switch (objt)
	{
	case TReal:
		return SNEW<Real>((double)num / (double)den);
	default:
		throw std::runtime_error("fraction can't be converted.");
		break;
	}
}

SBasic HM::Real::operate(Operator, SBasic &)
{
	return SBasic();
}

SBasic HM::Real::simplify()
{
	return SNEW<Real>(value);
}

SBasic HM::Real::Convert(ObjType objt)
{
	
	switch (objt)
	{
	case HM::TReal:
		return std::make_shared<Real>(value);
	case HM::TFrac:
	{
		int num = 0;
		int den = 0;
		int test = value;
		int tenV = 1;
		while (1)
		{
			if (isEqual(test, value))
			{
				num = test;
				den = value;
				SFraction ret = SNEW<Fraction>(num,den);
				ret->simplify();
				return ret;
			}
			else
			{
				tenV *= 10;
				value *= 10;
				test = value;
			}
		}
	}
		break;
	case HM::TIrretional:
	default:
		std::runtime_error("real can't be converted.");
		break;
	}
	
}
