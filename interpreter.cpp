#include <iostream>
#include <string>
#include <cmath>
#include "memtrace.h"
#include "operation.h"
#include "operator.h"
#include "calculator.h"
#include "interpreter.h"
using std::string;
string Calculator::resultStr;
string Calculator::expression;
Operation* Calculator::operations;
Interpreter::Interpreter(const string& expr){
  expression = expr;
  clear();
}
void Interpreter::execute(){
  operations = new Operation("0", expression, Operator::Operators::ADD);
  interpret(operations);
}
void Interpreter::interpret(Operation* operation){
  if(operation->operand1->isExpression()) interpretAddition(operation->operand1);
  if(operation->operand2->isExpression()) interpretAddition(operation->operand2);
}
void Interpreter::interpretAddition(Operand* operand){//BUG: Operand& ???
  string expr = (static_cast<Expression*>(operand))->getExpression();
  unsigned int brackets = 0;
  for (int i = expr.length() - 1; i >= 0; i--)
    switch (expr[i]) {
      case ')': brackets++; break;
      case '(': brackets--; break;
      case '+':
        if(brackets > 0) break;
        (static_cast<Expression*>(operand))->operation = new Operation(expr.substr(0, i), expr.substr(i + 1, expr.length() - (i + 1)), Operator::Operators::ADD);
        interpret((static_cast<Expression*>(operand))->operation);
        return;
      case '-':
        if(brackets > 0) break;
        (static_cast<Expression*>(operand))->operation = new Operation(expr.substr(0, i), expr.substr(i + 1, expr.length() - (i + 1)), Operator::Operators::SUB);
        //TODO: lehetne new Operation(expr.substr(0, i), '-' + expr.substr(i + 1, expr.length() - (i + 1)), Operator::Operators::ADD);
        interpret((static_cast<Expression*>(operand))->operation);
        return;
    }
  this->interpretMultiplication(operand);
}
void Interpreter::interpretMultiplication(Operand* operand){
  string expr = (static_cast<Expression*>(operand))->getExpression();
  unsigned int brackets = 0;
  for (int i = expr.length() - 1; i >= 0; i--)
    switch (expr[i]) {
      case ')': brackets++; break;
      case '(': brackets--; break;
      case '*':
        if(brackets > 0) break;
        (static_cast<Expression*>(operand))->operation = new Operation(expr.substr(0, i), expr.substr(i + 1, expr.length() - (i + 1)), Operator::Operators::MUL);
        interpret((static_cast<Expression*>(operand))->operation);
        return;
      case '/':
        if(brackets > 0) break;
        (static_cast<Expression*>(operand))->operation = new Operation(expr.substr(0, i), expr.substr(i + 1, expr.length() - (i + 1)), Operator::Operators::DIV);
        interpret((static_cast<Expression*>(operand))->operation);
        return;
    }
  this->interpretSpecialOperation(operand);
}
void Interpreter::interpretSpecialOperation(Operand* operand){
  string expr = (static_cast<Expression*>(operand))->getExpression();
  if(!expr.find("sin")){
    (static_cast<Expression*>(operand))->operation = new Operation(expr.substr(3, expr.length() - 3), "0", Operator::Operators::SIN);
    interpret((static_cast<Expression*>(operand))->operation);
    return;
  }
  if(!expr.find("cos")){
    (static_cast<Expression*>(operand))->operation = new Operation(expr.substr(3, expr.length() - 3), "0", Operator::Operators::COS);
    interpret((static_cast<Expression*>(operand))->operation);
    return;
  }
  if(!expr.find("tan")){
    (static_cast<Expression*>(operand))->operation = new Operation(expr.substr(3, expr.length() - 3), "0", Operator::Operators::TG);
    interpret((static_cast<Expression*>(operand))->operation);
    return;
  }
  if(!expr.find("log(")){
    bool found = false;
    size_t comma = 4;
    for (size_t brackets = 0; comma < expr.length() - 1; comma++){
      switch (expr[comma]) {
        case ')': brackets++; break;
        case '(': brackets--; break;
        case ',':
          if(brackets > 0) break;
          found = true; break;
      }
      if(found) break;
    }
    if(!found) throw std::invalid_argument("Invalid expression");
    (static_cast<Expression*>(operand))->operation = new Operation(expr.substr(4, comma - 4), expr.substr(comma + 1, expr.length() - comma - 2), Operator::Operators::LOG);//BUG: Mi van ha a vessző rossz helyen van
    interpret((static_cast<Expression*>(operand))->operation);
    return;
  }
  if(!expr.find("pow(")){
    bool found = false;
    size_t comma = 4;
    for (size_t brackets = 0; comma < expr.length() - 1; comma++){
      switch (expr[comma]) {
        case ')': brackets++; break;
        case '(': brackets--; break;
        case ',':
          if(brackets > 0) break;
          found = true; break;
      }
      if(found) break;
    }
    if(!found) throw std::invalid_argument("Invalid expression");
    (static_cast<Expression*>(operand))->operation = new Operation(expr.substr(4, comma - 4), expr.substr(comma + 1, expr.length() - comma - 2), Operator::Operators::POW);
    interpret((static_cast<Expression*>(operand))->operation);
    return;
  }
  if(!expr.find("sqrt")){
    (static_cast<Expression*>(operand))->operation = new Operation(expr.substr(4, expr.length() - 4), "0.5", Operator::Operators::POW);
    interpret((static_cast<Expression*>(operand))->operation);
    return;
  }
  throw std::invalid_argument("Invalid expression");
}
