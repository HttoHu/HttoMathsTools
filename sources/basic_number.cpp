#include "../include/basic_number.h"
#include "../include/algorithm.h";
#include <algorithm>
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
		auto ret = SNEW<Fraction>(ret_num, ret_den);
		ret->simplify();
		return ret;
	}
	case TReal:
	{
		auto real_obj = std::static_pointer_cast<Fraction>(obj->convert(TFrac));
		if (real_obj->real_mod() || real_mod())
		{

			return convert(TReal)->operate(operation, obj);
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
double HM::Fraction::to_double() const
{
	return (double)(num) / (double)den;
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
std::string HM::Fraction::to_string()const
{
	if (den > 1000)
		return std::to_string(value);
	if (den == 1)
		return std::to_string(num);
	return std::to_string(num) + "/" + std::to_string(den);
}
SBasic HM::Fraction::convert(ObjType objt)
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
	if(den>1000)
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
			return operate(operation, tmp->convert(ObjType::TReal));
		else
		{
			auto frac = convert(ObjType::TFrac);
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

double HM::Real::to_double() const
{
	return value;
}

bool HM::Real::is_integer()
{
	int a = (int)value;
	return (double)a == value;
}

SBasic HM::Real::convert(ObjType objt)
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

double HM::Surd::to_double() const
{
	return outside * std::sqrt(inside);
}

SBasic HM::Surd::operate(Operator operation, const SBasic & obj)
{
	switch (obj->get_type())
	{
	case TReal:
		throw std::runtime_error("Remember to do somthing here.");
		break;
	case TSurd:
	{
		auto tmp = std::static_pointer_cast<Surd>(obj);
		switch (operation)
		{
		case Operator::TIM:
		{
			int ret_outside = tmp->outside*outside;
			int ret_inside = tmp->inside*inside;
			auto ret = SNEW<Surd>(ret_outside, ret_inside);
			ret->simplify();
			return ret;
		}
		default:
			throw std::runtime_error("Remember to do somthing here.");
			break;
		}
	}
	default:
		throw std::runtime_error("Remember to do somthing here.");
	}
}

SBasic HM::Surd::simplify()
{
	auto vec = split_number(inside);
	int v = 1;
	int _inside = inside;
	int old_v = vec[0];
	for (int i = 1; i < vec.size(); i++)
	{
		if (old_v == vec[i])
		{
			v *= old_v;
			old_v = 1;
			_inside /= vec[i] * vec[i];
		}
		else
		{
			old_v = vec[i];
		}
	}
	outside *= v;
	inside = _inside;
	return SNEW<Surd>(outside, inside);
}

std::string HM::Surd::to_string()const
{
	if (inside > 10000)
	{
		return std::to_string(value);
	}
	if (inside == 1)
		return std::to_string(outside);
	else if (outside == 1)
		return "sqrt(" + std::to_string(inside) + ")";
	else if (outside == -1)
	{
		return "-sqrt(" + std::to_string(inside) + ")";
	}
	return std::to_string(outside) + "sqrt(" + std::to_string(inside) + ")";
}

SBasic HM::Surd::convert(ObjType objt)
{
	switch (objt)
	{
	case TReal:
		return SNEW<Real>(value);
	case Oppsite:
		return SNEW<Surd>(-outside, inside);
	default:
		throw std::runtime_error("type from surd convert into other type failed");
	}
}

bool HM::Surd::real_mod()
{
	if(inside>10000)
		simplify();
	if (inside > 10000)
	{
		value = outside * std::sqrt(inside);
		return true;
	}
	return false;
}

void HM::SurdBunch::insert_element(const SSurd & obj)
{
	expr.push_back(std::make_shared<Surd>(obj->inside,obj->outside));
}

SBasic HM::SurdBunch::operate(Operator operation, const SBasic & obj)
{
	switch (obj->get_type())
	{
	case TSBunch:
	{
		auto tmp = std::static_pointer_cast<SurdBunch>(obj);
		std::vector<SSurd> ret_vec = tmp->expr;
		switch (operation)
		{
		case HM::PLUS:
		{
			ret_vec.insert(ret_vec.end(), expr.begin(), expr.end());
			SSB ret = SNEW<SurdBunch>(ret_vec);
			return ret;
		}
		case HM::MINUS:
		{
			for (const auto & a : ret_vec)
			{
				a->outside = -a->outside;
			}
			ret_vec.insert(ret_vec.end(), expr.begin(), expr.end());
			SSB ret = SNEW<SurdBunch>(ret_vec);
			return ret;
		}
		default:
			throw std::runtime_error("Unfinished");
			break;
		}

	}
	case TSurd:
	{
		auto ret = SNEW<SurdBunch>(expr);
		switch (operation)
		{
		case PLUS:
			ret->insert_element(std::static_pointer_cast<Surd>(obj));
			return ret;
		case MINUS:
			ret->insert_element(std::static_pointer_cast<Surd>(obj->convert(Oppsite)));
			return ret;
		default:
			throw std::runtime_error("Unfinished");
			break;
		}

	}
	default:
		throw std::runtime_error("Unfinished");
		break;
	}
}

SBasic HM::SurdBunch::simplify()
{
	for (auto & a : expr)
	{
		a->simplify();
	}
	
	std::sort(expr.begin(), expr.end(), [](const auto &rn, const auto &rn2) {   return rn->inside > rn2->inside; });
	std::vector <SSurd>ret_expr;
	std::size_t index = 1;
	SSurd tmp_surd = SNEW<Surd>(0);
	std::vector<SSurd>temp;
	for (const auto &a : expr)
	{
		temp.push_back(a);
	}
	while (index < temp.size())
	{
		if (temp[index]->inside == temp[index - 1]->inside)
		{
			tmp_surd->outside = temp[index]->outside + temp[index - 1]->outside;
			tmp_surd->inside = temp[index]->inside;
			if (tmp_surd->outside == 0)
			{
				temp.erase(temp.begin() + index-1);
				temp.erase(temp.begin() + index-1);
				continue;
			}
			temp.erase(temp.begin() + index-1);
			temp.erase(temp.begin() + index-1);
			temp.insert(temp.begin() + (index - 1), tmp_surd);
			tmp_surd= SNEW<Surd>(0);
			continue;
		}
		index++;
	}
	expr = temp;
	if (expr.size() == 1)
		return expr[0];
	else
		return SNEW<SurdBunch>(expr);
}

std::string HM::SurdBunch::to_string()const
{
	std::string ret;
	if (expr.size() != 0)
	{
		ret += expr[0]->to_string();
	}
	else
		return "0";
	for (int i = 1; i < expr.size(); i++)
	{
		if (expr[i]->outside > 0)
			ret += '+';
		ret += expr[i]->to_string();
	}
	return ret;
}

SBasic HM::SurdBunch::convert(ObjType objt)
{
	switch (objt)
	{
	case HM::TReal:
	{
		double sum = 0;
		for (const auto &a : expr)
		{
			sum += a->value;
		}
		return SNEW<Real>(sum);
	}
	default:
		throw std::runtime_error("rmd");
		break;
	}
}

double HM::SurdBunch::to_double() const
{
	double ret = 0.0;
	for (const auto &a : expr)
	{
		ret += a->to_double();
	}
	return ret;
}
