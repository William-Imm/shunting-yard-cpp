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
		enum LastAdded { Queue, Stack, None };
		virtual bool handle_input(const char c, std::deque<std::string> & output_queue, std::stack<char> & operator_stack, LastAdded last_added) const;
		virtual bool handle_term(const std::string term, std::stack<double> & result_stack) const;
	public:
		Equation(); // default, blank constructor
		Equation(const std::string & equation);
		virtual ~Equation();
		double evaluate() const;
		std::string infix() const;
		void infix(const std::string & equation);
		void infix(const char * equation);
		std::queue<std::string> rpn() const;
		std::string rpn_tostring() const;
		friend std::ostream & operator<<(std::ostream & os, const Equation & equation);
	};
}
