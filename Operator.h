#ifndef OPERATOR_H
#define OPERATOR_H

#include "AST.h"
#include <string>

class Operator: public AST {
  std::string op;
  AST* left;
  AST* right;
public:
  Operator(const std::string& input, AST* lhs, AST* rhs); 

  ~Operator();

  // Required helper functions.
  int arity()         const;
  int associativity() const;
  int precedence()    const;

  // Required member functions.
  std::string infix()   const;
  std::string postfix() const;
  std::string prefix()  const;
};

#endif
