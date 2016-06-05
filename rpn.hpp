// Function definitions for Reverse Polish Notation parser
// William Immendorf - 2016

#include <queue>
#include <string>

std::queue<char> convert_to_rpn(std::string expression);
int evaluate(std::queue<char> expression);
