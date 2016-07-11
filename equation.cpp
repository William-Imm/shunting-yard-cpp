// Implemtation of equation class
// William Immendorf - 2016

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <locale>
#include <queue>
#include <stdexcept>

#include "equation.hpp"
#include "utility.hpp"

namespace EquParser
{
	Equation::Equation()
	{
		// This space intentionally left blank
	}
	
	Equation::Equation(const std::string equation) : infix_equation(equation)
	{
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
		using std::cout;
		using std::endl;
		std::stack<int> result_stack;
		std::locale loc;

		if (rpn_equation.empty())
		{
			cout << "Error: No expression present, are you sure you entered a valid infix expression?" << endl;
			exit(EXIT_FAILURE);
		}

		for (char term : rpn_equation)
		{
			if (isspace(term, loc))
				continue;
			else if (isdigit(term, loc))
				result_stack.push(term - '0');
			else
			{
				try 
				{
					switch (term)
					{
						case '+':
							result_stack = process_operator(result_stack, [] (int val1, int val2) { return val1 + val2; });
							break;
						case '-':
							result_stack = process_operator(result_stack, [] (int val1, int val2) { return val2 - val1; });
							break;
						case '*':
							result_stack = process_operator(result_stack, [] (int val1, int val2) { return val1 * val2; });
							break;
						case '/':
							result_stack = process_operator(result_stack, [] (int val1, int val2) { return val1 / val2; });
							break;
						case '^':
							result_stack = process_operator(result_stack, [] (int val1, int val2) { return pow(val1, val2); });
							break;
						default:
							std::string error = "Unrecognized symbol ";
							error.push_back(term);
							throw std::runtime_error(error);
					}
				}
				catch (std::runtime_error& e)
				{
					cout << "Exception: " << e.what() << endl;
					exit(EXIT_FAILURE);
				}
			}
		}

		if (result_stack.size() == 1)
		{
			return result_stack.top();
		}
		else
		{
			cout << "Error: Too many values in result stack" << endl;
			exit(EXIT_FAILURE);
		}
	}

	void Equation::convert_to_rpn()
	{
		std::queue<char> output_queue;
		std::stack<char> operator_stack;
		std::locale loc;

		for (char c : infix_equation)
		{
			if (isspace(c, loc) || isalpha(c, loc))
				continue;
			else if (isdigit(c, loc))
				output_queue.push(c);
			else if (c == '(')
				operator_stack.push(c);
			else if (c == ')')
			{
				if (!operator_stack.empty())
				{
					char top_operator = operator_stack.top();
					while (top_operator != '(')
					{
						output_queue.push(top_operator);
						operator_stack.pop();
						if (operator_stack.empty())
						{
							std::cout << "Error: Unclosed parenthesis expression. Exiting." << std::endl;
							exit(EXIT_FAILURE);
						}
						top_operator = operator_stack.top();
					}
					operator_stack.pop(); // get rid of used parenthesis
				}
				else 
				{
					std::cout << "Error: Cannot close a parenthesis with no operators. Exiting." << std::endl;
					exit(EXIT_FAILURE);
				}
			}
			else
			{
				if (!operator_stack.empty())
				{
					char top_operator = operator_stack.top();
					if (precendence_less_than(c, top_operator))
					{
						output_queue.push(top_operator);
						operator_stack.pop();
					}
				}
				operator_stack.push(c);
			}
		}
		
		while (!output_queue.empty())
		{
			rpn_equation.push_back(output_queue.front());
			rpn_equation.push_back(' ');
			output_queue.pop();
		}

		while (!operator_stack.empty())
		{
			rpn_equation.push_back(operator_stack.top());
			rpn_equation.push_back(' ');
			operator_stack.pop();
		}
	}
}
