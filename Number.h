#ifndef NUMBER_H
#define NUMBER_H

#include "AST.h"
#include <string>

class Number: public AST {
  double mVal;
public:
  Number(const std::string& input);
  // Destructor?

  // Required helper functions.
  int arity()         const;
  int associativity() const;
  int precedence()    const;

  // Required member functions.
  std::string infix()   const;
  std::string postfix() const;
  std::string prefix()  const;

  void print();
};

#endif
