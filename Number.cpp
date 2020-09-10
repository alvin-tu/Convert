#include "Number.h"
#include "Operator.h"
#include <sstream>
#include <iostream>
#include <cctype>
// Implement Number member functions here.

Number::Number(const std::string& input) {
    mVal = std::stod(input);
}

int Number::arity() const{
    return 0;
}

int Number::associativity() const{
    return 0;
}

int Number::precedence() const{
    return 5;
}

std::string Number::infix() const {
    std::stringstream stream;
    stream << mVal;
    return stream.str();
}

std::string Number::postfix() const {
    std::stringstream stream;
    stream << mVal;
    return stream.str();   
}

std::string Number::prefix()  const{
    std::stringstream stream;
    stream << mVal;
    return stream.str();  
}

void Number::print() {
    std::cout << mVal << std::endl;
}
