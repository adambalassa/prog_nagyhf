#ifndef DERIVATIVE_HEADER
#define DERIVATIVE_HEADER
#include <iostream>
#include <sstream>
#include <string>
#include "memtrace.h"
#include "calculator.h"
#include "logger.h"
#include "simplifier.h"
using std::string;
class Derivative: public Calculator{
public:
  Derivative(){  }
  void execute(){
    Simplifier::simplifyVariables(this->operations); //finds coefficients and indexes of variables
    try{
      Operation* derivative = this->operations->derivative(); //gets the derivative Abstract tree
      Simplifier::simplifyMethods(derivative); //deletes addition  with zero, multiplication with one, etc.
      std::stringstream ss;
      ss << derivative->operand2->echo();
      delete derivative;
      resultStr = ss.str();
    }
    catch(string s){
      resultStr = s;
    }
  }
  ~Derivative(){ }
};
#endif
