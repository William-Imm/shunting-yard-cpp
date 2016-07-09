// Class descriptor for Equation
// William Immendorf - 2016

#pragma once
#include <string>

namespace EquParser
{
	class Equation
	{
	public:
		Equation(); // default, blank constructor
		Equation(const std::string equation);
		int evaluate();
		std::string getInfixEquation();
		std::string getRPNEquation();
	private:
		std::string infixEquation;
		std::string rpnEquation;
		void convertToRPN();
	};
}
