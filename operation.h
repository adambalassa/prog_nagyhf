#ifndef OPERATION_HEADER
#define OPERATION_HEADER
#include <iostream>
#include <string>
#include <sstream>
#include "memtrace.h"
#include "operator.h"
using std::string;
class Operand;
class Operation{
private:
  void simplify(string&)const;
protected:
  Operator* procedure; // Operator for the operation
public:
  Operand* operand1; //TODO: PointerArray<Operation> operands;
  Operand* operand2;
  double getValue(double)const; //returns the value of the operation after substitution
  Operation(){}
  Operation(string, string, Operator::Operators); // Creates the operation by declaring operands
  Operation(Operand*, Operand*, Operator::Operators);
  bool operator==(const Operator::Operators& op)const{ return *procedure == op; }
  Operation* clone();
  string echo() const; // returns itself written in a string (recursive)
  Operation* derivative()const; //derivates itself
  virtual ~Operation();
};
#include "operand.h"
#endif
