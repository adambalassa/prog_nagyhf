#include "operation.h"
#include "operand.h"
#include "operator.h"
#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
using std::string;

Operation::Operation(string op1, string op2, Operator::Operators op): procedure(new Operator(op)), operand1(nullptr), operand2(nullptr){
  simplify(op1); simplify(op2);
  try{ this->operand1 = new Number(Number::isNum(op1)); }
  catch(...){
    if(op1 == string(1, Variable::varChar)) this->operand1 = new Variable();
    else this->operand1 = new Expression(op1);
  }

  try{ this->operand2 = new Number(Number::isNum(op2)); }
  catch(...){
    if(op2 == string(1, Variable::varChar)) this->operand2 = new Variable();
    else this->operand2 = new Expression(op2);
  }
}
Operation::Operation(Operand* op1, Operand* op2, Operator::Operators op): procedure(new Operator(op)), operand1(op1), operand2(op2){
}
void Operation::simplify(string& expressionString)const{
  for (size_t brackets = 0; true; expressionString = expressionString.substr(1, expressionString.length() - 2)) {
    if(expressionString[0] != '(' || expressionString[expressionString.length() - 1] != ')') return;
    for (size_t i = 0; i < expressionString.length() - 2; i++) {
      switch (expressionString[i]) {
        case '(':
          brackets++;
          break;
        case ')':
          brackets--;
          if(!brackets) return;
          break;
      }
    }
  }
}
Operation::~Operation(){
  delete operand1; operand1 = nullptr;
  delete operand2; operand2 = nullptr;
  delete procedure; procedure = nullptr;
}
double Operation::getValue(double d)const{
  return this->procedure->execute(this->operand1->returnValue(d), this->operand2->returnValue(d));
}
string Operation::echo()const{
  std::stringstream ss;
  if(this->procedure->isNormal) ss << '(' << this->operand1->echo() << ' ' << this->procedure->echo() << ' ' << this->operand2->echo() << ')';
  else if(this->procedure->isSpecial) ss << this->procedure->echo() << '(' << this->operand1->echo() << ", " << this->operand2->echo() << ')';
  else ss << this->procedure->echo() << '(' << this->operand1->echo() << ')';
  return ss.str();
}
Operation* Operation::derivative()const{
  return procedure->derivative(operand1, operand2);
}
Operation* Operation::clone(){
  return new Operation(
    this->operand1->clone(),
    this->operand2->clone(),
    this->procedure->get()
  );
}
