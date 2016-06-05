// Main function, takes a infix equation, converts to RPN, and evaluates
// William Immendorf - 2016

#include <iostream>
#include <queue>
#include <string>

#include "rpn.hpp"

int main()
{
	using namespace std;
	string expression;

	cout << "Enter an expression: ";
	getline(cin, expression);
	queue<char> rpn_expression = convert_to_rpn(expression);
	int result = evaluate(rpn_expression);

	cout << "Evaluated result: " << result << endl;
}
