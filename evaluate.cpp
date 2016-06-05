// Evaluate a Reverse Polish Notation expression
// William Immendorf - 2016
// Compile with --std=c++11

#include <cmath> // for pow
#include <cstdlib> // for exit
#include <functional>
#include <iostream>
#include <locale>
#include <queue>
#include <stack>
#include <stdexcept>

#include "rpn.hpp"

bool enough_on_stack(std::stack<int> stack, int size)
{
	if (stack.size() < size)
	{
		return false;
	}
	return true;
}

std::stack<int> process_operator(std::stack<int> num_stack, std::function<int (int val1, int val2)> expression)
{
	if (enough_on_stack(num_stack, 2))
	{
		int val1 = num_stack.top();
		num_stack.pop();
		int val2 = num_stack.top();
		num_stack.pop();
		num_stack.push(expression(val1, val2));
	}
	else
		throw std::runtime_error("Not enough arguments for an operator");
	return num_stack;
}

int evaluate(std::queue<char> expression)
{
	using namespace std;
	stack<int> result_stack;
	locale loc;

	if (expression.empty())
	{
		cout << "Error: No expression present, are you sure you entered a valid infix expression?" << endl;
		exit(EXIT_FAILURE);
	}

	do
	{
		char term = expression.front();
		expression.pop();
		if (isdigit(term, loc))
		{
			result_stack.push(term - '0');
		}
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
						string error = "Unreconized symbol ";
						error.push_back(term);
						throw runtime_error(error);
				}
			}
			catch (runtime_error& e)
			{
				cout << "Exception: " << e.what() << endl;
				exit(EXIT_FAILURE);
			}
		}
	} while (!expression.empty());

	if (result_stack.size() == 1)
	{
		return result_stack.top();
	}
	else
	{
		cout << "Error: Too many values in result stack " << endl;
		exit(EXIT_FAILURE);
	}
}
