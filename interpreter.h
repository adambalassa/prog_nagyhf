#ifndef INTERPRETER_HEADER
#define INTERPRETER_HEADER
#include <string>
#include <cmath>
#include "memtrace.h"
#include "operation.h"
#include "operand.h"
#include "calculator.h"
using std::string;
class Interpreter: public Calculator{
private:
//  void removeWhiteSpaces(const string&)const; // Removes all spaces from a string
  void interpret(Operation*); // Transform string into an operation tree
  void interpretAddition(Operand*); // Decides if expression is an addition
  void interpretMultiplication(Operand*); // Decides if expression is an addition
  void interpretSpecialOperation(Operand*); // Interprets special operations
public:
  Interpreter(){}
  Interpreter(const string&);
  void execute(); // Initializes the interpretation of the expressionString
  ~Interpreter(){}
};
#endif
