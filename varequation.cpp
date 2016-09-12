// Class implentation for VariableEquation
// William Immendorf - 2016

#include <locale>

#include "varequation.hpp"

namespace EquParser
{
	VariableEquation::VariableEquation()
	{
		x = 0.0;
	}
	
	VariableEquation::VariableEquation(const std::string & equation) : Equation(equation)
	{
		x = 0.0;
		convert_to_rpn();
	}

	VariableEquation::VariableEquation(const std::string & equation, const double x) : Equation(equation)
	{
		this->x = x;
		convert_to_rpn();
	}

	VariableEquation::VariableEquation(const Equation & equation, const double x) : Equation(equation)
	{
		this->x = x;
		convert_to_rpn();
	}

	// Handle X variable in infix
	bool VariableEquation::handle_input(const char c, std::deque<std::string> & output_queue, std::stack<char> & operator_stack)
	{
		std::locale loc;
		if (c == 'X' || c == 'x')
		{
			std::string last_term = output_queue.back();
			output_queue.push_back("X");
			// If last term is a digit, mutiply it by X
			if (isdigit(last_term[0], loc))
			{
				output_queue.push_back("*");
			}
			return true;
		}
		return false;
	}

	// Handle X when evaluating equation
	bool VariableEquation::handle_term(const std::string term, std::stack<double> & result_stack)
	{
		if (term == "X")
		{
			result_stack.push(x);
			return true;
		}
		return false;
	}
}
