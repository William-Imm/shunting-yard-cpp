// Main function, takes a infix equation, converts to RPN, and evaluates
// William Immendorf - 2016

#include <iostream>
#include <string>

#include "equation.hpp"

int main()
{
	std::string expression;

	std::cout << "Enter an expression: ";
	std::getline(std::cin, expression);
	EquParser::Equation equation = expression;
	std::cout << equation.get_rpn_equation() << std::endl;
	std::cout << "Evaluated result: " << equation.evaluate() << std::endl;
}
