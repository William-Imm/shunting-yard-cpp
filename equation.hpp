// Class descriptor for Equation
// William Immendorf - 2016

#pragma once
#include <iostream>
#include <queue>
#include <string>

namespace EquParser
{
	class Equation
	{
	private:
		std::string infix_equation = "";
		std::queue<char> rpn_equation;
		void convert_to_rpn();
	public:
		Equation(); // default, blank constructor
		Equation(const std::string & equation);
		int evaluate();
		std::string get_infix_equation() const;
		std::queue<char> get_rpn_equation() const;
		std::string rpn_to_string() const;
		friend std::ostream & operator<<(std::ostream & os, const Equation equation);
	};
}
