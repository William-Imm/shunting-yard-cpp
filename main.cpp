// Main function, takes a infix equation, converts to RPN, and evaluates
// William Immendorf - 2016

#include <iostream>
#include <string>

#include "varequation.hpp"

int main()
{
	std::string expression;
	double x;
	using EquParser::VariableEquation;

	std::cout << "Enter an expression: ";
	std::getline(std::cin, expression);
	std::cout << "Enter a X value: ";
	std::cin >> x;
	VariableEquation equation(expression, x);
	std::cout << equation << std::endl;
	double result = equation.evaluate();
	std::cout << "Evaluated result: " << result << std::endl;
}
