#ifndef LOGGER_HEADER
#define LOGGER_HEADER
#include <iostream>
#include <sstream>
#include <string>
#include "memtrace.h"
#include "operation.h"
#include "calculator.h"
using std::string;
class Logger: public Calculator{
public:
  Logger(){ }
  void execute(){
    std::stringstream ss;
    ss << this->operations->operand2->echo(); //writes operationtree
    resultStr = ss.str();
  }
  ~Logger(){}
};
#endif
