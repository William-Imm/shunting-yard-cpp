// Class implentation for VariableEquation
// William Immendorf - 2016

#include <locale>

#include "varequation.hpp"

namespace EquParser
{
	VariableEquation::VariableEquation()
	{
		varx = 0.0;
	}

	VariableEquation::VariableEquation(const char * equation, const double x) : Equation(), varx(x)
	{
		infix(equation);
	}
	
	VariableEquation::VariableEquation(const std::string & equation, const double x) : Equation(), varx(x)
	{
		infix(equation);
	}

	VariableEquation::VariableEquation(const Equation & equation, const double x) : Equation(equation), varx(x)
	{
		// Left blank
	}

	// Handle X variable in infix
	bool VariableEquation::handle_input(const char c, std::deque<std::string> & output_queue, std::stack<char> & operator_stack) const
	{
		std::locale loc;
		std::string last_term;
		bool empty = true;
		if (c == 'X' || c == 'x')
		{
			if (!output_queue.empty())
			{
				last_term = output_queue.back();
				empty = false;
			}
			output_queue.push_back("X");
			// If last term is a digit, mutiply it by X
			if (!empty && isdigit(last_term[0], loc))
			{
				operator_stack.push('*');
			}
			return true;
		}
		else if (c == '(')
		{
			// Special case for X variable, add an additional multiply operator if it preceeds the open parenthesis (like a number)
			std::string last_term = output_queue.back();
			if (last_term[0] == 'X' || isdigit(last_term[0], loc))
			{
				operator_stack.push('*');
			}
			operator_stack.push(c);
			return true;
		}
		return false;
	}

	// Handle X when evaluating equation
	bool VariableEquation::handle_term(const std::string term, std::stack<double> & result_stack) const
	{
		if (term == "X")
		{
			result_stack.push(varx);
			return true;
		}
		return false;
	}
}
