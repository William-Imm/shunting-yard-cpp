// Converts infix equations to reverse polish notation
// Uses shunting yard algorithm.
// William Immendorf - 2016
// Compile with --std=c++11

#include <cstdlib> // for exit
#include <iostream>
#include <locale> // for isdigit and isspace
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>

#include "rpn.hpp"

struct operator_detail 
{
	int precendence;
	bool right_associative;
};

const std::unordered_map<char, operator_detail> operator_map 
{
	{'+', {2, false}},
	{'-', {2, false}},
	{'*', {3, false}},
	{'/', {3, false}},
	{'^', {4, true}}
};

bool precendence_less_than(char op1, char op2)
{
	auto op_iterator1 = operator_map.find(op1);
	auto op_iterator2 = operator_map.find(op2);

	if (op_iterator1 != operator_map.end() && op_iterator2 != operator_map.end())
	{
		if (op_iterator1->second.right_associative)
		{
			if (op_iterator1->second.precendence < op_iterator2->second.precendence)
				return true;
		}
		else 
		{
			if (op_iterator1->second.precendence <= op_iterator2->second.precendence)
				return true;
		}
	}

	return false;
}

std::queue<char> convert_to_rpn(std::string expression)
{
	std::queue<char> output_queue;
	std::stack<char> operator_stack;
	std::locale loc;

	for (char c : expression)
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
						std::cout << "Error: Unclosed parnthesis expression. Exiting." << std::endl;
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
	std::queue<char> result_queue;

	while (!output_queue.empty())
	{
		std::cout << output_queue.front() << " ";
		result_queue.push(output_queue.front());
		output_queue.pop();
	}

	while (!operator_stack.empty())
	{
		std::cout << operator_stack.top() << " ";
		result_queue.push(operator_stack.top());
		operator_stack.pop();
	}

	std::cout << std::endl;
	return result_queue;
}
