#include "../include/basic_number.h"
#include "../include/algorithm.h";
using namespace HM;
#define SNEW std::make_shared
double _count(Operator op, double v1, double v2)
{
	switch (op)
	{
	case PLUS:
		return v1 + v2;
	case MINUS:
		return v1 - v2;
	case TIM:
		return v1 * v2;
	case DIV:
		return v1 / v2;
	default:
		std::runtime_error("type convert failed");
	}
}

bool isEqual(int n, float f)
{
	if ((float)n == f)
		return true;
	else
		return false;
}

SBasic HM::Fraction::operate(Operator operation, const SBasic & obj)
{
	switch (obj->get_type()) {
	case TFrac:
	{
		auto fra_obj = std::static_pointer_cast<Fraction>(obj);
		if (fra_obj->real_mod() || real_mod())
		{
			return SNEW<Real>(_count(operation, value, fra_obj->value));
		}
		int ret_num;
		int ret_den;
		switch (operation)
		{
		case PLUS:
			ret_den = den * fra_obj->den;
			ret_num = num * fra_obj->den + fra_obj->num*den;
			break;
		case MINUS:
			ret_den = den * fra_obj->den;
			ret_num = num * fra_obj->den - fra_obj->num*den;
			break;
		case TIM:
			ret_den = den * fra_obj->den;
			ret_num = num * fra_obj->num;
			break;
		case DIV:
			ret_den = den * fra_obj->num;
			ret_num = num * fra_obj->den;
			break;
		}
		auto ret= SNEW<Fraction>(ret_num, ret_den);
		ret->simplify();
		return ret;
	}
	case TReal:
	{
		auto real_obj = std::static_pointer_cast<Fraction>(obj->Convert(TFrac));
		if (real_obj->real_mod()||real_mod())
		{
			
			return Convert(TReal)->operate(operation, obj);
		}
		else
		{
			return operate(operation, real_obj);
		}
	}
	default:
		std::runtime_error("syntax error");
	}
}
SBasic HM::Fraction::simplify()
{
	std::vector<int> num_vec = split_number(std::abs(num));
	std::vector<int> den_vec = split_number(std::abs(den));
	cut_same_element(num_vec, den_vec);
	num = num / std::abs(num);
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
	if (real_mod() == true)
		return std::to_string(value);
	if (den == 1)
		return std::to_string(num);
	return std::to_string(num) + "/" + std::to_string(den);
}
SBasic HM::Fraction::Convert(ObjType objt)
{
	switch (objt)
	{
	case TReal:
		return SNEW<Real>(value);
	default:
		throw std::runtime_error("fraction can't be converted.");
		break;
	}
}

bool HM::Fraction::real_mod()
{
	simplify();
	if (den > 1000)
	{
		value = (double)num / (double)den;
		return true;
	}
	return false;
}

SBasic HM::Real::operate(Operator operation, const SBasic & obj)
{
	switch (obj->get_type())
	{
	case TReal:
	{
		switch (operation)
		{
		case PLUS:
			return SNEW<Real>(value + std::static_pointer_cast<Real>(obj)->value);
		case MINUS:
			return SNEW<Real>(value - std::static_pointer_cast<Real>(obj)->value);
		case DIV:
			return SNEW<Real>(value / std::static_pointer_cast<Real>(obj)->value);
		case TIM:
			return SNEW<Real>(value * std::static_pointer_cast<Real>(obj)->value);
		default:
			throw std::runtime_error("unsupported operation");
		}
	}
	case TFrac:
	{

		auto tmp = std::static_pointer_cast<Fraction>(obj);
		if (tmp->real_mod())
			return operate(operation, tmp->Convert(ObjType::TReal));
		else
		{
			auto frac = Convert(ObjType::TFrac);
			frac->simplify();
			return frac->operate(operation, tmp);
		}
		break;
	}
	default:
		throw std::runtime_error("syntax error");
	}
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
		double v = value;
		int num = 0;
		int den = 0;
		int test = v;
		int tenV = 1;
		while (1)
		{
			if (isEqual(test, v))
			{
				num = test;
				den = tenV;
				SFraction ret = SNEW<Fraction>(num, den);
				ret->simplify();
				return ret;
			}
			else
			{
				tenV *= 10;
				v *= 10;
				test = v;
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
