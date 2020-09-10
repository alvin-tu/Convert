#ifndef AST_H
#define AST_H

#include <istream>
#include <string>

class AST {
public:
  // Parse a postfix (Reverse Polish) expression into an AST.
  // Throw an exception with an error message if something goes wrong.
  static AST* parse_postfix(std::istream& tokens);

  // Parse a prefix (Polish) expression into an AST.
  // Throw an exception with an error message if something goes wrong.
  static AST* parse_prefix(std::istream& tokens);

protected:
  // Helper functions.  These will be useful when converting
  // ASTs to infix notation.  These aren't intended for public
  // use, so pick whatever return values make sense to you.

  // How many arguments does this token consume?
  virtual int arity() const = 0;

  // If this operator is associative, how?
  virtual int associativity() const = 0;

  // How tightly does this operator bind to its operands?
  virtual int precedence() const = 0;

  // Needed to allow your member functions to call
  // the helper functions on other AST instances:
  friend class Number;
  friend class Operator;

public:

  // Render the AST as an infix string.
  virtual std::string infix() const = 0;

  // Render the AST as a postfix string.
  virtual std::string postfix() const = 0;

  // Render the AST as a prefix string.
  virtual std::string prefix() const = 0;

  // Don't forget!
  virtual ~AST() {}
};

#endif
