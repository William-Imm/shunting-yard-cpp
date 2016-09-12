// Utility function defintions for the program
// William Immendorf - 2016

#pragma once
#include <functional>
#include <stack>
#include <string>

namespace EquParser
{
	bool precendence_less_than(const char op1, const char op2);
	void process_operator(std::stack<double> & num_stack, std::function<double (double val1, double val2)> expression);
}
