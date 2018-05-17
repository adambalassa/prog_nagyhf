#ifndef SIMPLIFIER_HEADER
#define SIMPLIFIER_HEADER
#include "memtrace.h"
#include "calculator.h"
#include "operation.h"
#include "operand.h"
#include "operator.h"
using std::string;
class Simplifier: public Operation{
  static void findMultipledVar(Operation*); //deletes coefficients using getCoeffAndIndex
  static void findPoweredVar(Operation*);   //deletes indexes using getCoeffAndIndex
  static bool getCoeffAndIndex(Expression* expr, double& c, double& i); // finds multiplicated and powered variables and
                                                                        // writes their coefficients and indexes in c and i
  static void findAdditionWithZero(Operation*);
  static void findMultiplicationWithZero(Operation*);
  static void findBasicSimplifications(Operation*); // powered on first or zeroth, multiplicated by one

  static void deleteAdditionWithZero(Operand**);
  static void deleteBasicSimplifications(Operand**);
  static void deleteMultiplicationWithZero(Operand**);
public:
  Simplifier(){ }
  static void simplifyVariables(Operation* op){
    findPoweredVar(op);
    findMultipledVar(op);
  }
  static void simplifyMethods(Operation* op){
    findBasicSimplifications(op);
    findMultiplicationWithZero(op);
    findAdditionWithZero(op);
  }
  ~Simplifier(){ }
};
#endif
