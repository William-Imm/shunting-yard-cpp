// Class descriptor for Equation
// William Immendorf - 2016

#pragma once
#include <string>

namespace EquParser
{
	class Equation
	{
	private:
		std::string infix_equation = "";
		std::string rpn_equation = "";
		void convert_to_rpn();
	public:
		Equation(); // default, blank constructor
		Equation(const std::string & equation);
		int evaluate();
		std::string get_infix_equation();
		std::string get_rpn_equation();
	};
}
