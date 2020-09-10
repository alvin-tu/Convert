#include "AST.h"
#include "Number.h"
#include "Operator.h"
#include <iostream>
#include <sstream>
#include <string>


 int main(int argc, char** argv) {
  
  // Check your command line arguments...
  
  if (argc != 3) {
      std::cerr << "USAGE: convert [input-format] [output-format]\n";
      std::cerr << "  Valid input formats:   prefix, postfix\n";
      std::cerr << "  Valid output formats:  prefix, infix, postfix\n";
      exit(0);
    } 
    if((std::string(argv[1]) != "postfix" && std::string(argv[1]) != "prefix") || (std::string(argv[2]) != "postfix" 
    && std::string(argv[2]) != "prefix" && std::string(argv[2]) != "infix")) {
      std::cerr << "USAGE: convert [input-format] [output-format]\n";
      std::cerr << "  Valid input formats:   prefix, postfix\n";
      std::cerr << "  Valid output formats:  prefix, infix, postfix\n";
      exit(0);
    } 

    // get input, output expression
    std::string line;
    while(std::getline(std::cin, line)) {
      std::istringstream tokens(line);
      try {
        if(std::string(argv[1]) == "postfix") {
          AST* ast = AST::parse_postfix(tokens);
          
          if(std::string(argv[2]) == "postfix") {
            std::cout << "=> " << ast->postfix() << std::endl;
          }

          else if(std::string(argv[2]) == "prefix") {
            std::cout << "=> " << ast->prefix() << std::endl;
          }

          else if(std::string(argv[2]) == "infix") {
            std::cout << "=> " << ast->infix() << std::endl;
          }
          delete ast;
        }
        else if(std::string(argv[1]) == "prefix") {
          
          AST* ast = AST::parse_prefix(tokens);
          std::string line;
          if(tokens >> line) {
            std::cerr << "Too many operands." << std::endl;
            delete ast;
            continue;
          }

          if(std::string(argv[2]) == "postfix") {
            std::cout << "=> " << ast->postfix() << std::endl;
          }

          else if(std::string(argv[2]) == "prefix") {
            std::cout << "=> " << ast->prefix() << std::endl;
          }

          else if(std::string(argv[2]) == "infix") {
            std::cout << "=> " << ast->infix() << std::endl;
          }
          delete ast;
        }
    }
    catch(const std::exception& e) {
      std::cout << e.what() << std::endl;
    }
  }

  return 0;
}
