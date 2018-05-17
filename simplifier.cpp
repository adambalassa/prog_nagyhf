#include "memtrace.h"
#include "calculator.h"
#include "operation.h"
#include "operand.h"
#include "operator.h"
#include "simplifier.h"
using std::string;

void Simplifier::findPoweredVar(Operation* op){
  if(op->operand1->isExpression()){
    Expression* expr = static_cast<Expression*>(op->operand1);
    if(*(expr->operation) == Operator::Operators::POW && expr->operation->operand1->isVariable() && expr->operation->operand2->isNumber()){
      double index = expr->operation->operand2->returnValue(0);
      delete expr;
      op->operand1 = new Variable(index);
    }
    else findPoweredVar(expr->operation);
  }
  if(op->operand2->isExpression()){
    Expression* expr = static_cast<Expression*>(op->operand2);
    if(*(expr->operation) == Operator::Operators::POW && expr->operation->operand1->isVariable() && expr->operation->operand2->isNumber()){
      double index = expr->operation->operand2->returnValue(0);
      delete expr;
      op->operand2 = new Variable(index);
    }
    else findPoweredVar(expr->operation);
  }
}
void Simplifier::findMultipledVar(Operation* op){
  if(op->operand1->isExpression()){
    double index, coeff;
    if(getCoeffAndIndex(static_cast<Expression*>(op->operand1), coeff, index)){
      delete op->operand1;
      op->operand1 = new Variable(index, coeff);
    }
    else findMultipledVar((static_cast<Expression*>(op->operand1))->operation);
  }
  if(op->operand2->isExpression()){
    double index, coeff;
    if(getCoeffAndIndex(static_cast<Expression*>(op->operand2), coeff, index)){
      delete op->operand2;
      op->operand2 = new Variable(index, coeff);
    }
    else findMultipledVar((static_cast<Expression*>(op->operand2))->operation);
  }
}
bool Simplifier::getCoeffAndIndex(Expression* expr, double& c, double& i){
  if(*(expr->operation) == Operator::Operators::MUL){
    if(expr->operation->operand1->isVariable() && expr->operation->operand2->isNumber()){
      i = (static_cast<Variable*>(expr->operation->operand1))->getIndex();
      c = expr->operation->operand2->returnValue(0);
      return true;
    }
    if(expr->operation->operand2->isVariable() && expr->operation->operand1->isNumber()){
      i =(static_cast<Variable*>(expr->operation->operand2))->getIndex();
      c = expr->operation->operand1->returnValue(0);
      return true;
    }
    return false;
  }
  if(*(expr->operation) == Operator::Operators::DIV && expr->operation->operand1->isVariable() && expr->operation->operand2->isNumber()){
    i = (static_cast<Variable*>(expr->operation->operand1))->getIndex();
    c = 1 / expr->operation->operand2->returnValue(0);
    return true;
  }
  return false;
}

void Simplifier::findAdditionWithZero(Operation* op){
  if(op->operand1->isExpression())
    deleteAdditionWithZero(&(op->operand1));
  if(op->operand2->isExpression())
    deleteAdditionWithZero(&(op->operand2));
}
void Simplifier::deleteAdditionWithZero(Operand** op){
  Expression* expr = *((Expression**)op);
  findAdditionWithZero(expr->operation);
  double operand1Val = expr->operation->operand1->returnValue(0);
  double operand2Val = expr->operation->operand1->returnValue(0);
  if(*(expr->operation) == Operator::Operators::ADD){ /// X + 0
    if(expr->operation->operand1->isNumber() && operand1Val > -0.00000000001 && operand1Val < 0.00000000001){
      Operand* other = expr->operation->operand2->clone();
      delete expr;
      *op = other;
    }
    else if(expr->operation->operand2->isNumber() && operand2Val > -0.00000000001 && operand2Val < 0.00000000001){
      Operand* other = expr->operation->operand1->clone();
      delete expr;
      *op = other;
    }
  }
  else if(*(expr->operation) == Operator::Operators::SUB){ /// X - 0
    if(expr->operation->operand2->isNumber() && operand2Val > -0.00000000001 && operand2Val < 0.00000000001){
      Operand* other = expr->operation->operand1->clone();
      delete expr;
      *op = other;
    }
  }
}
void Simplifier::findMultiplicationWithZero(Operation* op){
  if(op->operand1->isExpression())
    deleteMultiplicationWithZero(&(op->operand1));
  if(op->operand2->isExpression())
    deleteMultiplicationWithZero(&(op->operand2));
}
void Simplifier::deleteMultiplicationWithZero(Operand** op){
  Expression* expr = *((Expression**)op);
  findMultiplicationWithZero(expr->operation);
  if(*(expr->operation) == Operator::Operators::MUL){ /// X * 0
    double operand1Val = expr->operation->operand1->returnValue(0);
    double operand2Val = expr->operation->operand1->returnValue(0);
    if((expr->operation->operand1->isNumber() && operand1Val > -0.00000000001 && operand1Val < 0.00000000001) ||
       (expr->operation->operand2->isNumber() && operand2Val > -0.00000000001 && operand2Val < 0.00000000001))
    {
      delete expr;
      *op = new Number(0);
    }
  }
}
void Simplifier::findBasicSimplifications(Operation* op){
  if(op->operand1->isExpression())
    deleteBasicSimplifications(&(op->operand1));
  if(op->operand2->isExpression())
    deleteBasicSimplifications(&(op->operand2));
}
void Simplifier::deleteBasicSimplifications(Operand** op){
  Expression* expr = *((Expression**)op);
  findBasicSimplifications(expr->operation);
  double operand1Val = expr->operation->operand1->returnValue(0);
  double operand2Val = expr->operation->operand1->returnValue(0);
  if(*(expr->operation) == Operator::Operators::MUL){ /// X * 1
    if(expr->operation->operand1->isNumber() && operand1Val > 1-0.00000000001 && operand1Val < 1.00000000001){
      Operand* other = expr->operation->operand2->clone();
      delete expr;
      *op = other;
    }
    else if(expr->operation->operand2->isNumber() && operand2Val > 1-0.00000000001 && operand2Val < 1.00000000001){
      Operand* other = expr->operation->operand1->clone();
      delete expr;
      *op = other;
    }
  }
  else if(*(expr->operation) == Operator::Operators::POW){ /// X ^ 1
    if(expr->operation->operand2->isNumber() && operand2Val > 1-0.00000000001 && operand2Val < 1.00000000001){
      Operand* other = expr->operation->operand1->clone();
      delete expr;
      *op = other;
    }
    else if(expr->operation->operand2->isNumber() && operand2Val > -0.00000000001 && operand2Val < 0.00000000001){
      delete expr;
      *op = new Number(1);
    }
  }
  else if(*(expr->operation) == Operator::Operators::LOG){ ///log(a, a)
    if(expr->operation->operand2->isNumber() && operand1Val > operand2Val - 0.00000000001 && operand1Val < operand2Val + 0.00000000001){
      delete expr;
      *op = new Number(1);
    }
  }

}
