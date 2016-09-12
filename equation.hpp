// Class descriptor for Equation
// William Immendorf - 2016

#pragma once
#include <deque>
#include <iostream>
#include <queue>
#include <stack>
#include <string>

namespace EquParser
{
	class Equation
	{
	private:
		std::string infix_equation = "";
		std::queue<std::string> rpn_equation;
	protected:
		// Rules for handling characters in raw infix equation
		void convert_to_rpn();
		virtual bool handle_input(const char c, std::deque<std::string> & output_queue, std::stack<char> & operator_stack);
		virtual bool handle_term(const std::string term, std::stack<double> & result_stack);
	public:
		Equation(); // default, blank constructor
		Equation(const std::string & equation);
		virtual ~Equation();
		double evaluate();
		std::string get_infix_equation() const;
		std::queue<std::string> get_rpn_equation();
		std::string rpn_to_string();
		friend std::ostream & operator<<(std::ostream & os, Equation equation);
	};
}
