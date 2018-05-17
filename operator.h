#ifndef OPERATOR_HEADER
#define OPERATOR_HEADER
#include <iostream>
#include <sstream>
#include "memtrace.h"
using std::string;
class Operation;
class Operand;
class Operator{
public:
  bool isNormal; // returns if operation is not addition or multiplication
  bool isSpecial;
  enum Operators { ADD, SUB, MUL, DIV, LOG, SIN, COS, TG, POW };
  Operator(){}
  Operator(Operators);
  double execute(double, double)const; // executes the operation for a propriate amount of operands
  string echo()const;
  bool operator==(const Operator::Operators& op)const{ return procedure == op; }
  Operation* derivative(Operand* op1, Operand* op2)const;
  Operators get()const; //getter for Operators procedure
  ~Operator(){}
protected:
  Operators procedure;
};
#endif
