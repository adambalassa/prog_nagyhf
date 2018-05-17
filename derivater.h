#ifndef DERIVATER_HEADER
#define DERIVATER_HEADER
#include "memtrace.h"
#include "operation.h"
#include "calculator.h"
#include "operand.h"
using std::string;
class Derivater: public Calculator{
private:
  static double x0;
  const double punctuality = 0.0000001;
public:
  Derivater(){}
  void setOperands(const string& o1, const string& x = ""){ x0 = Number::isNum(o1); } //sets x0
  void execute(){
    double result = (operations->getValue(x0 + punctuality) - operations->getValue(x0)) / punctuality; //derivates by definition
    result += (operations->getValue(x0) - (operations->getValue(x0 - punctuality))) / punctuality;
    prepareresultStr(result / 2);
  }
  ~Derivater(){}
};
double Derivater::x0;
#endif
