# Convert
by: Alvin Tu

## Overview

This project is a program that lets you convert expressions into different formats.
The program will read expressions in either prefix or postfix notation and 
then output them in any notation.

The completed program will run like this:

```
[alvintu@Alvins-Laptop convert]$ ./convert prefix infix
1.2.3.4
Invalid token: 1.2.3.4
+ 3 4
=> 3 + 4
  - 5 - -7 9
=> 5 - (-7 - 9)
```

## The Program

The program takes two arguments on the command line.  The first is the
name of an input format, and the second is the name of an output format. If it
does't receive exactly two arguments, or if either argument isn't a valid format,
print the following usage message and exit:

```
USAGE: convert [input-format] [output-format]
  Valid input formats:   prefix, postfix
  Valid output formats:  prefix, infix, postfix
```

If the command line arguments are valid, the program will read from standard
input one line at a time.  Each line will be an expression  in the input format;
parse it into an  **abstract syntax tree** (AST).  Then convert it to the output
format and  print the result.  When the program reachs the end of the input stream, 
it should exit.


## Input Formats

Each line of input will consist of a series of **tokens**.  Tokens are separated
by whitespace.  An input line may have leading or trailing spaces,  and may have
multiple spaces between  tokens.  Read each line  according to the input  format
specified on the command line:

- If the input format is `prefix` then parse each line as a prefix expression
  (also known as Polish Notation).

- If the input format is `postfix` then parse each line as a postfix expression
  (also known as Reverse Polish Notation). 

When an error is encountered, the following error messages will be printed,
then the program will move on to the next line of input.

- If you encounter an invalid token, print `Invalid token: XXX` (where `XXX` is
  the token you couldn't parse).

- If any operator doesn't have enough operands, or if there are no tokens in the
  input, print `Not enough operands.`.

- If there are too many operands for a single expression or extra tokens at the
  end of the expression, print `Too many operands.`.

## Output Formats

- If the output format is `prefix` then print the expression in Polish Notation.

- If the output format is `postfix` then print the expression in Reverse Polish
  Notation.

- If the output format is `infix`  then print the expression in the  usual human
  infix notation. Add as few parentheses as are necessary to guarantee that your
  infix expression has  the same structure as your AST.  See the Operators table
  in the Reference section for order of operations rules.

  ```
  [alvintu@Alvins-Laptop]$ ./convert postfix infix
  1 2 + 3 +
  => 1 + 2 + 3
  4 5 6 + +
  => 4 + (5 + 6)
  7 8 9 * +
  => 7 + 8 * 9
  108 ~
  => ~ 108
  ```

Formatting was done by  the AST member functions  named after each  output
format. 

## Reference

### Numbers

All numbers are `double`s.  Numbers in the input will always be in this format:

- Optionally: A `+` or `-` indiciating the sign.
- One or more decimal digits (`0` through `9`).
- Optionally: A `.` followed by one or more decimal digits.

### Operators

All operators are listed below (numbers are included for completeness):

| Symbol | Operation       | Arity | Associativity | Precedence |
|--------|-----------------|-------|---------------|------------|
| `+`    | Addition        | 2     | Left          | Lowest     |
| `-`    | Subtraction     | 2     | Left          | Lowest     |
| `*`    | Multiplication  | 2     | Left          | Low        |
| `/`    | Division        | 2     | Left          | Low        |
| `%`    | Remainder       | 2     | Left          | Low        |
| `~`    | Negation        | 1     | Right*        | Medium     |
| `^`    | Exponentiation  | 2     | Right         | High       |
| Number | Literal Value   | 0     | None          | Highest    |

Note that the values in the Associativity and Precedence columns only make sense
when working with infix notation. In the other notations, order of operations is
determined by the order of the tokens in the input stream.

