// Implemtation of equation class
// William Immendorf - 2016

#include "equation.hpp"
#include "utility.hpp"

namespace EquParser
{
	Equation::Equation()
	{
		infix_equation = "";
		rpn_equation = "";
	}
	
	Equation::Equation(const std::string equation)
	{
		infix_equation = equation;
		convert_to_rpn();
	}

	std::string Equation::get_infix_equation()
	{
		return infix_equation;
	}

	std::string Equation::get_rpn_equation()
	{
		return rpn_equation;
	}

	int Equation::evaluate()
	{

	}
}
