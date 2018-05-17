#ifndef OPERAND_HEADER
#define OPERAND_HEADER
#include <iostream>
#include <sstream>
#include <cmath>
#include "memtrace.h"
#include "operation.h"
#define PI 3.14159265358979323846
#define E 2.71828182845904523536
using std::string;
class Operand{
protected:
  enum OperandType { EXPRESSION, NUMBER, VARIABLE };
  OperandType type;
public:
  Operand(OperandType o): type(o){  }
  bool isExpression()const{return type == EXPRESSION;}
  bool isNumber()const{return type == NUMBER;}
  bool isVariable()const{return type == VARIABLE;}
  virtual Operand* derivative()const = 0; //enables an operand to derivate itself
  virtual double returnValue(double) const= 0; //returns value after substituting the given double
  virtual string echo()const = 0; //returns itself written in string
  virtual Operand* clone() = 0; // makes a clone of itself (recursively)
  virtual ~Operand(){}
};

/****************
 *  EXPRESSION  *
 ****************/
class Expression: public Operand{
private:
  string expressionString;
public:
  Operation* operation; //This is a node of the Binary tree
  Expression(const string& str): Operand(EXPRESSION), expressionString(str), operation(nullptr){ }
  Expression(Operation* op): Operand(EXPRESSION), expressionString("---"), operation(op){ }
  string echo()const{ return operation->echo(); } //recursion
  string getExpression() const{ return expressionString; }
  Operand* derivative()const{ return new Expression(operation->derivative()); }
  ~Expression(){ delete operation; operation = nullptr;}
  Operand* clone(){ return new Expression(this->operation->clone()); }
  double returnValue(double d) const { return operation->getValue(d); }
};
/*              *
 *EXPRESSIONEND *
 *              */
/****************
*     NUMBER    *
*****************/
class Number: public Operand{
private:
  double value;
public:
  Number(): Operand(NUMBER), value(0){ }
  Number(double val): Operand(NUMBER), value(val){ }
  Operand* derivative()const{ return new Number(0); }
  static double isNum(const string& str){ //throws an exception if given string is not a number. else it returns the value
    try{
      for (size_t i = 1; i < str.length(); i++)
        if(!isdigit(str[i]) && str[i] != '.')  throw "Not a number";
       return std::stod(str);
    }
    catch(...){
      if(str == "PI" || str == "pi") return PI;
      if(str == "E" || str == "e") return E;
      throw "Not a number";
    }
  }
  string echo()const{
    std::stringstream ss;
    ss << value;
    return ss.str();
  }
  Operand* clone(){ return new Number(this->value); }
  double returnValue(double d = 0) const{ return value; }
  ~Number(){ }
};
/*              *
 *  ENDNUMBER   *
 *              */
/*****************
*   VARIABLE    *
*****************/
class Variable: public Operand{
private:
  double index;
  double coefficient;
public:
  static const char varChar = 'x';
  Variable(double i = 1, double c = 1): Operand(VARIABLE), index(i), coefficient(c){ }
  ~Variable(){ }
  Operand* derivative()const{
    if(coefficient * index < 0.000000001 && coefficient * index > -0.000000001 )
      return new Number(0);
    if(index - 1 < 0.00000000001 && index - 1 > -0.00000000001)
      return new Number(coefficient * index);
    return new Variable(index - 1, coefficient * index);
  }
  double getIndex()const { return index; }
  Operand* clone(){ return new Variable(this->index, this->coefficient); }
  double returnValue(double d) const{ return coefficient * pow(d, index); }
  string echo() const{
    std::stringstream ss;
    if(coefficient != 1) ss << coefficient;
    if(index != 0) {
      ss << varChar;
      if(index != 1) ss << '^'<< index;
    }
    else if(coefficient > -0.00000000001 && coefficient < 0.00000000001){
      ss << 1;
    }
    return ss.str();
  }
};
/*              *
 *  ENDVARIABLE *
 *              */
#endif
