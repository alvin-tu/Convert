#include "AST.h"
#include "Number.h"
#include "Operator.h"
#include <iostream>
#include <sstream>
#include <stack>
#include <stdexcept>

// Check if a token is an operator
bool isOperator(const std::string& input) {
	if (input == "+" || input == "-" || input == "*" || input == "/" 
  || input == "^" || input == "%" || input == "~") {
		return true;
	}
	else {
		return false;
	}
}

// check if the input is valid
bool isNum(const std::string& input) {
    bool num = true;
    int testCount = 0;
    int minCount = 0;
    int plusCount = 0;
    int dotCount = 0;
    int n = input.length();

    if(isOperator(input)) {
        return false;
    }
    for(int i = 0; i < n; i ++) {
        if(isalpha(input[i])) {
            num = false;
            break;
        } else if(input[i] == '-' && minCount == 0 && testCount == 0 && plusCount != 1) {
            minCount += 1;
        } else if(input[i] == '+' && plusCount == 0 && testCount == 0 && minCount != 1){
            plusCount += 1;
        } else if (input[i] == '.' && dotCount == 0) {
            dotCount += 1;
        } else if(isdigit(input[i])) {
            testCount += 1;
        } else if(input[i] == '-' && (minCount == 1 || plusCount == 1)) {
            num = false;
            break;
        } else if(input[i] == '+' && (plusCount == 1 || minCount == 1)) {
            num = false;
            break;         
        } else if(input[i] == '.' && dotCount == 1) {
            num = false;
            break;     
        } else if(ispunct(input[i]) && (input[i] != '.' || input[i] != '-' || input[i] != '+') && !isOperator(input)) {
            num = false;
            break;  
        }
    }

    return num;
}

// if it is prefix, this helper function will parse
AST* AST::parse_prefix(std::istream& tokens) {
    std::string token;
    AST* num = NULL;

    try {
        if(!(tokens >> token)) {                                        // check invalid cases first
            throw std::runtime_error("Not enough operands.");
        }
        if(!isNum(token) && !isOperator(token)) {
            throw std::runtime_error("Invalid token: " + token);
        } 
        // base case, return the number
        else if(isNum(token)) {
            num = new Number(token);
            return num;
        }
    }
    catch(...) {
        delete num;
        throw;
    }

    if(token == "~") {
        AST* right = NULL;
        try {
            right = AST::parse_prefix(tokens);
            return new Operator("~", NULL, right);
        }
        catch(...) {
            delete right;
            throw;
        }
    }
    else {

        // recursion to parse the input
        AST* right = NULL;
        AST* left = NULL;
        try {
            left = AST::parse_prefix(tokens);
            right = AST::parse_prefix(tokens);
            return new Operator(token, left, right);
        }
        catch(...) {
            delete left;
            delete right;
            throw;
        }
    }
    
}

// parse the postfix inputs
AST* AST::parse_postfix(std::istream& tokens) {
    std::string token;
    std::stack<AST*> stack;
    AST* right;
    AST* left;
    AST* pushTree;
    try{
        while(tokens >> token) { 
            if(token == "~") {
                if(stack.empty()) {
                    throw std::runtime_error("Not enough operands.");
                }
                right = stack.top();
                stack.pop();
                pushTree = new Operator(token, NULL, right);
                stack.push(pushTree);
                continue;
            }

            if(isOperator(token) && token != "~") {
                if(stack.empty()) {
                    throw std::runtime_error("Not enough operands.");
                }
                right = stack.top();
                stack.pop();
                if(stack.empty()) {
                    delete right;
                    throw std::runtime_error("Not enough operands.");
                }
                left = stack.top();
                stack.pop();
                pushTree = new Operator(token, left, right);
                stack.push(pushTree);
                continue;
            }
            else if(isNum(token)) {
                stack.push(new Number(token));
                continue;
            } 
            else {
                throw std::runtime_error("Invalid token: " + token);
            }
        }
        if(stack.size() == 0) {
            throw std::runtime_error("Not enough operands.");
        }
        if(stack.size() > 1) {
            throw std::runtime_error("Too many operands.");
        }
        return stack.top();
    }
    catch(...) {
        while(!stack.empty()) {
            delete stack.top();
            stack.pop();
        }
        throw;
    }
}