// Utility function defintions for the program
// William Immendorf - 2016

#pragma once
#include <functional>
#include <stack>
#include <string>

namespace EquParser
{
	bool precendence_less_than(const char op1, const char op2);
	std::stack<int> process_operator(std::stack<int> & num_stack, std::function<int (int val1, int val2)> expression);
}
