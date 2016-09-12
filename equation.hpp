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
		void convert_to_rpn();
	protected:
		// Rules for handling characters in raw infix equation
		virtual void handle_input(char c, std::deque<std::string> & output_queue, std::stack<char> & operator_stack);
		virtual void handle_term(char term, std::stack<double> & result_stack);
	public:
		Equation(); // default, blank constructor
		Equation(const std::string & equation);
		virtual ~Equation();
		double evaluate();
		std::string get_infix_equation() const;
		std::queue<std::string> get_rpn_equation() const;
		std::string rpn_to_string() const;
		friend std::ostream & operator<<(std::ostream & os, const Equation equation);
	};
}
