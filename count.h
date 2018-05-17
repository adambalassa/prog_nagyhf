#ifndef COUNT_HEADER
#define COUNT_HEADER
#include "memtrace.h"
#include "operation.h"
#include "calculator.h"
#include "operand.h"
using std::string;
class Count: public Calculator{
private:
  static double substitute;
public:
  Count(){}
  void execute(){ // gets the value by substituting the substitute
    double result = operations->getValue(substitute);
    prepareresultStr(result);
  }
  void setOperands(const string& o1, const string& o2 = ""){ substitute = Number::isNum(o1); } //sets the substitute
  ~Count(){}
};
double Count::substitute;
#endif
