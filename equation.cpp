// Implemtation of equation class
// William Immendorf - 2016

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <locale>
#include <stdexcept>

#include "equation.hpp"
#include "utility.hpp"

namespace EquParser
{
	Equation::Equation()
	{
		// This space intentionally left blank
	}
	
	Equation::Equation(const std::string & equation) : infix_equation(equation)
	{
		convert_to_rpn();
	}

	Equation::~Equation()
	{
		// This makes the linker happy.
	}

	void Equation::handle_input(char c, std::deque<std::string> & output_queue, std::stack<char> & operator_stack)
	{
		// TODO
	}

	void Equation::handle_term(char term, std::stack<double> & result_stack)
	{
		// TODO
	}

	std::string Equation::get_infix_equation() const
	{
		return infix_equation;
	}

	std::queue<std::string> Equation::get_rpn_equation() const
	{
		return rpn_equation;
	}

	std::string Equation::rpn_to_string() const
	{
		std::queue<std::string> clone_queue(rpn_equation);
		std::string result;
		while (!clone_queue.empty())
		{
			result.append(clone_queue.front());
			result.push_back(' ');
			clone_queue.pop();
		}
		return result.substr(0, result.length() - 1);;
	}

	double Equation::evaluate()
	{
		using std::cout;
		using std::endl;
		std::stack<double> result_stack;
		std::queue<std::string> clone_queue(rpn_equation);
		std::locale loc;

		if (rpn_equation.empty())
		{
			cout << "Error: No expression present, are you sure you entered a valid infix expression?" << endl;
			exit(EXIT_FAILURE);
		}

		while (!clone_queue.empty())
		{
			std::string term = clone_queue.front();
			clone_queue.pop();
			if (isspace(term[0], loc))
				continue;
			else if (isdigit(term[0], loc))
				result_stack.push(std::stod(term));
			else
			{
				try 
				{
					switch (term[0])
					{
						case '+':
							process_operator(result_stack, [] (double val1, double val2) { return val1 + val2; });
							break;
						case '-':
							process_operator(result_stack, [] (double val1, double val2) { return val2 - val1; });
							break;
						case '*':
							process_operator(result_stack, [] (double val1, double val2) { return val1 * val2; });
							break;
						case '/':
							process_operator(result_stack, [] (double val1, double val2) { return val1 / val2; });
							break;
						case '^':
							process_operator(result_stack, [] (double val1, double val2) { return pow(val1, val2); });
							break;
						default:
							std::string error = "Unrecognized symbol ";
							error.append(term);
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
		std::deque<std::string> output_queue;
		std::stack<char> operator_stack;
		std::locale loc;

		bool decimal = false;

		for (char c : infix_equation)
		{
			if (isspace(c, loc) || isalpha(c, loc))
				continue;
			else if (isdigit(c, loc))
			{
				if (decimal)
				{
					std::string prev_string = output_queue.back();
					output_queue.pop_back();
					prev_string.push_back(c);
					output_queue.push_back(prev_string);
				}
				else
					output_queue.push_back(std::string(1, c));
			}
			else if (c == '.')
			{
				if (decimal)
					continue;
				else
				{
					std::string prev_string = output_queue.back();
					if (isdigit(prev_string[0],loc))
					{
						output_queue.pop_back();
						prev_string.push_back('.');
						output_queue.push_back(prev_string);
						decimal = true;
					}
					else
						continue;
				}
			}
			else if (c == '(')
				operator_stack.push(c);
			else if (c == ')')
			{
				if (!operator_stack.empty())
				{
					char top_operator = operator_stack.top();
					while (top_operator != '(')
					{
						output_queue.push_back(std::string(1, top_operator));
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
						output_queue.push_back(std::string(1, top_operator));
						operator_stack.pop();
					}
				}
				operator_stack.push(c);
			}
			if (c != '.' && !isdigit(c, loc))
			{
				decimal = false;
			}
		}
		
		while (!output_queue.empty())
		{
			rpn_equation.push(output_queue.front());
			output_queue.pop_front();
		}

		while (!operator_stack.empty())
		{
			rpn_equation.push(std::string(1, operator_stack.top()));
			operator_stack.pop();
		}
	}

	std::ostream & operator<<(std::ostream & os, const Equation equation)
	{
		os << equation.rpn_to_string();
		return os;
	}
}
