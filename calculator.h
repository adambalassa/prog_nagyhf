#ifndef CALCULATOR_HEADER
#define CALCULATOR_HEADER
#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include "memtrace.h"
#include "operation.h"
using std::string;

class Calculator{
protected:
  static Operation* operations; // A static pointer to the operationtree
  static string resultStr; // A string where any result of the calcuations are stored
  static string expression; // The string that's operations are calculated
  void prepareresultStr(double result){
    std::stringstream ss;
    if(result > 10000000)
      ss << "Infinite";
    else if(result - (int)result > -0.0000001 && result - (int)result < 0.0000001)
      ss << round(result);
    else
      ss << result;
    resultStr = ss.str();
  } // Prepares the resultstring for the user
  void clear(){ delete operations; operations = nullptr; } // deletes the operationtree
public:
  Calculator(){};
  virtual void execute() = 0; // -""-
  virtual void setOperands(const std::string& o1 = "", const std::string& o2 = ""){}
  string& getResult()const{ return resultStr; }
  virtual ~Calculator(){  }
};
#endif
