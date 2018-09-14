#pragma once
/*
* Creation Date : 2018 8-6
* Edited by Htto 2018
*/
#include <memory>
#include <vector>
#include <iostream>
#include <string>
namespace HM
{
	class Basic;
	class Real;
	class Surd;
	class Fraction;
	class SurdBunch;
	using SSB = std::shared_ptr<SurdBunch>;
	using SBasic = std::shared_ptr<Basic>;
	using SReal = std::shared_ptr<Real>;
	using SFraction = std::shared_ptr<Fraction>;
	using SSurd = std::shared_ptr<Surd>;
	enum Operator
	{
		PLUS,MINUS,DIV,TIM,MOD
	};

	enum ObjType
	{
		TReal,TFrac,TIrretional,TSurd,TSBunch,
		Oppsite,
	};

	class Basic
	{
	public:
		Basic(ObjType type) :obj_type(type) {}
		virtual SBasic operate(Operator, const SBasic &s) = 0;
		virtual SBasic simplify() = 0;
		virtual std::string to_string()const
		{
			return "empty obj";
		}
		virtual SBasic convert(ObjType objt) = 0;
		virtual double to_double()const=0;
		ObjType get_type() { return obj_type; }
		virtual ~Basic(){}
	private:
		ObjType obj_type;
	};

	class Real final:public Basic
	{
	public:
		Real(double _value) :Basic(TReal),value(_value) {}
		SBasic operate(Operator, const SBasic &)override;
		SBasic simplify()override;
		double to_double()const override;
		bool is_integer();
		std::string to_string()const
		{
			return std::to_string(value);
		}
		SBasic convert(ObjType objt)override;
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
			value = (double)den / (double)num;
		}
		// ======= some methods derived from base class 
		SBasic operate(Operator, const SBasic &)override;
		double to_double()const override;
		SBasic simplify()override;
		std::string to_string()const override;
		SBasic convert(ObjType objt)override;
		//============================================
		bool real_mod();
	private:
		int num;
		int den;
		double value;
	};
	class SurdBunch :public Basic
	{
	public:
		SurdBunch() :SurdBunch(std::vector<SSurd>()) {}
		SurdBunch(const std::vector<SSurd> &_expr) :Basic(TSBunch), expr(_expr) {}
		void insert_element(const SSurd &obj);
		//===========================================
		SBasic operate(Operator, const SBasic &)override;
		SBasic simplify()override;
		std::string to_string()const override;
		SBasic convert(ObjType objt)override;
		double to_double()const override;
		//==========================================
	private:
		std::vector<SSurd> expr;
	};
	class Surd :public Basic
	{
	public:
		Surd(int _outside, int _inside) :Basic(TSurd), inside(_inside), outside(_outside)
		{
			value = outside * std::sqrt(inside);
		}
		Surd(int _inside) :Surd(1, _inside) {}
		//============================================
		double to_double()const override;
		SBasic operate(Operator, const SBasic &)override;
		SBasic simplify()override;
		std::string to_string()const override;
		SBasic convert(ObjType objt)override;
		//==============================================
		bool real_mod();
		friend SurdBunch;
	private:
		int inside;
		int outside;
		double value;
	};


}