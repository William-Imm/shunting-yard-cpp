// Main function, takes a infix equation, converts to RPN, and evaluates
// William Immendorf - 2016

#include <iostream>
#include <string>

#include "equation.hpp"

int main()
{
	std::string expression;
	using EquParser::Equation;

	std::cout << "Enter an expression: ";
	std::getline(std::cin, expression);
	Equation equation(expression);
	std::cout << equation << std::endl;
	double result = equation.evaluate();
	std::cout << "Evaluated result: " << result << std::endl;
}
