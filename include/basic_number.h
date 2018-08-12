#pragma once
/*
* Creation Date : 2018 8-6
* Edited by Htto 2018
*/
#include <memory>
#include <vector>
#include <string>
namespace HM
{
	class Basic;
	class Real;
	class Fraction;
	using SBasic = std::shared_ptr<Basic>;
	using SReal = std::shared_ptr<Real>;
	using SFraction = std::shared_ptr<Fraction>;

	enum Operator
	{
		PLUS,MINUS,DIV,TIM,MOD
	};

	enum ObjType
	{
		TReal,TFrac,TIrretional,
	};

	class Basic
	{
	public:
		Basic(ObjType type) :obj_type(type) {}
		virtual SBasic operate(Operator, SBasic &s) = 0;
		virtual SBasic simplify() = 0;
		virtual std::string to_string()
		{
			return "empty obj";
		}
		virtual SBasic Convert(ObjType objt) = 0;
		virtual ~Basic(){}
	private:
		ObjType obj_type;
	};

	class Real final:public Basic
	{
	public:
		Real(double _value) :Basic(TReal),value(_value) {}
		SBasic operate(Operator, SBasic &)override;
		SBasic simplify()override;
		std::string to_string()
		{
			return std::to_string(value);
		}
		SBasic Convert(ObjType objt)override;
	private:
		double value;
	};

	class Fraction :public Basic
	{
	public:
		Fraction(int _num, int _den) :Basic(TFrac), num(_num), den(_den) 
		{
			if (den == 0)
				throw std::runtime_error("den couldn't set zero");
		}
		SBasic operate(Operator, SBasic &)override;
		SBasic simplify()override;
		std::string to_string();
		SBasic Convert(ObjType objt)override;
	private:
		int num;
		int den;
	};
}