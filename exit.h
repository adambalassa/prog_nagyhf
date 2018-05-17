#ifndef EXIT_HEADER
#define EXIT_HEADER
#include "memtrace.h"
#include "calculator.h"
using std::string;
class Exit: public Calculator{
public:
  Exit(){ }
  void execute(){
    clear(); //clears the calculator's abstract tree
    resultStr = "";
  }
  ~Exit(){ }
};
#endif
