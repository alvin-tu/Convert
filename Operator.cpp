#include "Operator.h"
#include <iostream>
// Implement Operator member functions here.
Operator::Operator(const std::string& input, AST* lhs, AST* rhs) {
	op = input;
	left = lhs;
	right = rhs;
}

Operator::~Operator() {
	delete left;
	delete right;
}

int Operator::arity() const {
	if(op == "~") {
		return 1;
	}
	else {
		return 2;
	}
}

int Operator::associativity() const {
	if(op == "^") {
		return 1;
	}
	return -1;
}

int Operator::precedence() const {
	if(op == "+" || op == "-") {
		return 1;
	}
	else if(op == "*" || op == "/" || op == "%") {
		return 2;
	}
	else if(op == "~") {
		return 3;
	}
	else {
		return 4;
	}
}


std::string Operator::infix() const {
	std::string pRight = right->infix();
	if (right->precedence() < this->precedence()) {
		if(right->precedence() != 3) {
			pRight = "(" + pRight + ")";
		}
	}	  
	else if(right->precedence() == this->precedence() && this->precedence() != 3) {
		if(this->associativity() == -1) {
			pRight = "(" + pRight + ")";
		}
	}
	if(op == "~") {
		return op + " " + pRight;
	}

	std::string pLeft = left->infix();
	if(left->precedence() < this->precedence()) {
		pLeft = "(" + pLeft + ")";
	}
	else if(left->precedence() == this->precedence()) {
		if (left->associativity() == 1) {
			pLeft = "(" + pLeft + ")";
		}
	}
	return pLeft + " " + op + " " + pRight;
}

std::string Operator::postfix() const{
	if(op == "~") {
		return right->postfix() + " ~";
	}
	return left->postfix() + " " + right->postfix() + " " + op;
}

std::string Operator::prefix() const {
	if(op == "~") {
		return "~ " + right->prefix();
	}
	return op + " " + left->prefix() + " " + right->prefix();
}
