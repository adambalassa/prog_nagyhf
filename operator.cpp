#include <cmath>
#include <sstream>
#include "memtrace.h"
#include "operator.h"
#include "operation.h"
#include "operand.h"

Operator::Operator(Operators o){
  procedure = o;
  isSpecial = o == LOG;
  isNormal = (o == ADD || o == SUB || o == MUL || o == DIV || o == POW);
}
double Operator::execute(double a, double b = 0) const{
  switch (this->procedure) {
    case ADD:
      return a + b;
    case SUB:
      return a - b;
    case MUL:
      return a * b;
    case DIV:
      return a / b;
    case SIN:
      return sin(a);
    case COS:
      return cos(a);
    case TG:
      return tan(a);
    case POW:
      return pow(a, b);
    case LOG:
      return log(b) / log(a);
    default:
      return 0;
  }
}
string Operator::echo()const{
  switch (procedure) {
    case Operator::Operators::ADD:
      return "+";
    case Operator::Operators::SUB:
      return "-";
    case Operator::Operators::DIV:
      return "/";
    case Operator::Operators::MUL:
      return "*";
    case Operator::Operators::POW:
      return "^";
    case Operator::Operators::SIN:
      return "sin";
    case Operator::Operators::COS:
      return "cos";
    case Operator::Operators::LOG:
      return "log";
    case Operator::Operators::TG:
      return "tan";
    default: return "";
  }
}

Operation* Operator::derivative(Operand* op1, Operand* op2)const{
  switch (procedure) {
    case ADD:
      return new Operation(op1->derivative(), op2->derivative(), ADD);
    case SUB:
      return new Operation(op1->derivative(), op2->derivative(), SUB);
    case MUL:
      {Operation* leftSide = new Operation(op1->derivative(), op2->clone(), MUL);
      Operation* rightSide = new Operation(op1->clone(), op2->derivative(), MUL);
      return new Operation(new Expression(leftSide), new Expression(rightSide), ADD);}
    case DIV:
      {Operation* leftSide = new Operation(op1->derivative(), op2->clone(), MUL);
      Operation* rightSide = new Operation(op1->clone(), op2->derivative(), MUL);
      Operation* numerater = new Operation(new Expression(leftSide), new Expression(rightSide), ADD);
      Operation* denominator = new Operation(op2->clone(), op2->clone(), MUL);
      return new Operation(new Expression(numerater), new Expression(denominator), DIV);}
    case SIN:
      {Operation* derivated = new Operation(op1->clone(), new Number(0), COS);
      return new Operation(new Expression(derivated), op1->derivative(), MUL);}
    case COS:
      {Operation* derivated1 = new Operation(op1->clone(), new Number(0), SIN);
      Operation* derivated2 = new Operation(new Number(-1), new Expression(derivated1), MUL);
      return new Operation(new Expression(derivated2), op1->derivative(), MUL);}
    case TG:
      {Operation* derivated1 = new Operation(op1->clone(), new Number(0), COS);
      Operation* derivated2 = new Operation(new Expression(derivated1), new Number(-2), POW);
      return new Operation(new Expression(derivated2), op1->derivative(), MUL);}
    case POW:
      {if(op2->isNumber()){
        Operation* derivated1 = new Operation(op1->clone(), new Number(op2->returnValue(0) - 1), POW);
        Operation* derivated2 = new Operation(new Expression(derivated1), op1->derivative(), MUL);
        return new Operation(op2->clone(), new Expression(derivated2), MUL);
      }
      if(op1->isNumber()){
        Operation* derivated1 = new Operation(op1->clone(), op2->clone(), POW);
        Operation* derivated2 = new Operation(new Number(Number::isNum("e")), op1->clone(), LOG);
        Operation* derivated3 = new Operation(new Expression(derivated2), op2->derivative(), MUL);
        return new Operation(new Expression(derivated1), new Expression(derivated3), MUL);
      }
      Operation* derivated1 = new Operation(new Number(Number::isNum("e")), op1->clone(), LOG);
      Operation* derivated2 = new Operation(new Expression(derivated1), op2->clone(), MUL);
      Operation* derivated3 = new Operation(new Number(Number::isNum("e")), new Expression(derivated2), POW);
      Operation* returnOp = derivated3->derivative();
      delete derivated3;
      return returnOp;}
    case LOG:
      {if(!op1->isNumber()) {
        Operation* numerator = new Operation(new Number(Number::isNum("e")), op2->clone(), LOG);
        Operation* denominator = new Operation(new Number(Number::isNum("e")), op1->clone(), LOG);
        Operation* fraction = new Operation(new Expression(numerator), new Expression(denominator), DIV);
        Operation* returnOp = fraction->derivative();
        delete fraction;
        return returnOp;
      }
      Operation* derivated1 = new Operation(new Number(Number::isNum("e")), op1->clone(), LOG);
      Operation* derivated2 = new Operation(new Expression(derivated1), op2->clone(), MUL);
      return new Operation(op2->derivative(), new Expression(derivated2), DIV);}
    default:
      throw "This line should never appear";
  }
}
Operator::Operators Operator::get()const{
  return this->procedure;
}
