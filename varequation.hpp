// Class descriptor for VariableEquation
// William Immendof - 2016

#pragma once

#include "equation.hpp"

namespace EquParser
{
	class VariableEquation : public Equation
	{
		private:
			double varx;
		protected:
			virtual bool handle_input(const char c, std::deque<std::string> & output_queue, std::stack<char> & operator_stack) const;
			virtual bool handle_term(const std::string term, std::stack<double> & result_stack) const;
		public:
			VariableEquation();
			VariableEquation(const std::string & equation);
			VariableEquation(const std::string & equation, const double x);
			VariableEquation(const Equation & equation, const double x);
			double x() const { return varx; }
			void x(const double x) { varx = x; }
	};
}
