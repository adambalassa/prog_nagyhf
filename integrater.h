#ifndef INTEGRATER_HEADER
#define INTEGRATER_HEADER
#include "memtrace.h"
#include "operation.h"
#include "calculator.h"
using std::string;
class Integrater: public Calculator{
private:
  static double a, b;
  const int punctuality = 5000000;
  double integrate(){ //gets Riemann integral of an interval
    double result = 0;
    for (double i = a; i < b; i += (b - a) / punctuality)
      result += operations->getValue(i);
    return result / punctuality * (b - a);
  }
public:
  Integrater(){}
  void setOperands(const string& d1, const string& d2){ a = Number::isNum(d1); b = Number::isNum(d2); }
  void execute(){
    double result = integrate();
    prepareresultStr(result);
  }
  ~Integrater(){}
};
double Integrater::a, Integrater::b;
#endif
