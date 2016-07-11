// Utility function defintions for the program
// William Immendorf - 2016

#pragma once
#include <functional>
#include <stack>
#include <string>

namespace EquParser
{
	bool precendence_less_than(char op1, char op2);
	std::stack<int> process_operator(std::stack<int> num_stack, std::function<int (int val1, int val2)> expression);
}
