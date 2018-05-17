#include <sstream>
#include "memtrace.h"
#include "main.h"
//#define TESTING
#define MENTARCE
#define MEMTARCE

void createTesterStreams(std::istream& is, std::ostream& os);
void testOutput(std::istream&);
int main(){
  Main* program = new Main();

  #ifdef TESTING
    std::stringstream sIn;
    std::stringstream sOut;
    createTesterStreams(sOut, sIn);
    program->readCommands(sIn, sOut);
    std::cout << "\tTESTING: \n" << sIn.str() << "\n\n\tRESULTS: \n" << sOut.str();
    testOutput(sOut);
  #else
    program->readCommands();
  #endif
  delete program;
  return 0;
}
void createTesterStreams(std::istream& sOut, std::ostream& sIn){
  sIn << "\t\tcount 1: 2 * x - cos(pi / sin(pi / (2 * x))) + log(3, 9) * sqrt(pow(x, 2)) / tan(pi / 4)" << std::endl;
  sIn << "\t\tthis is not a valid line" << std::endl;
  sIn << "\t\tinvalid: 2" << std::endl;
  sIn << "\t\twrite" << std::endl;
  sIn << "\t\tcount: invalid" << std::endl;
  sIn << "\t\twrite" << std::endl;
  sIn << "\t\tintegrate 0 1: pow(x, 2)" << std::endl;
  sIn << "\t\twrite: sin(cos(x + 3))" << std::endl;
  sIn << "\t\tderivative: log(3, x) * 12" << std::endl;
  sIn << "\t\tderivate pi" << std::endl;
  sIn << "\t\tcount 0: 2 * pow(x, -1)" << std::endl;
  sIn << "\t\twrite" << std::endl;
  sIn << "\t\tderivative" << std::endl;
  sIn << "\t\twrite" << std::endl;
  sIn << "\t\texit" << std::endl; ///COMPULSORY!!!
}
void testOutput(std::istream& sOut){
  bool success = true;
  std::string buffer;

  getline(sOut, buffer);
  if(buffer != std::string("\t\t5")){ std::cout << "Hibas teszteset 1" << std::endl; success = false;} //SIMPLE CALCULATION
  getline(sOut, buffer);
  if(buffer != "\t\tInvalid command"){ std::cout << "Hibas teszteset 2" << std::endl; success = false;} //INVALID LINE
  getline(sOut, buffer);
  if(buffer != "\t\tInvalid command"){ std::cout << "Hibas teszteset 3" << std::endl; success = false;} //INVALID COMMAND, VALID EXPRESSION
  getline(sOut, buffer);
  if(buffer != "\t\t2"){ std::cout << "Hibas teszteset 3.1" << std::endl; success = false;} //THE EXPRESSION IS SAVED
  getline(sOut, buffer);
  if(buffer != "\t\tInvalid expression"){ std::cout << "Hibas teszteset 4" << std::endl; success = false;} //VALID COMMAND, INVALID EXPRESSION
  getline(sOut, buffer);
  if(buffer != "\t\t0"){ std::cout << "Hibas teszteset 5" << std::endl; success = false;} //AFTER INVALID EXPRESSION, IT IS SET BACK TO 0
  getline(sOut, buffer);
  if(buffer != "\t\t0.333333"){ std::cout << "Hibas teszteset 6" << std::endl; success = false;} //INTERGAL
  getline(sOut, buffer);
  if(buffer != "\t\tsin(cos((x + 3)))"){ std::cout << "Hibas teszteset 7" << std::endl; success = false;} // LOGGING
  getline(sOut, buffer);
  if(buffer != "\t\t((1 / (log(e, 3) * x)) * 12)"){ std::cout << "Hibas teszteset 8" << std::endl; success = false;} //DERIVATIVE
  getline(sOut, buffer);
  if(buffer != "\t\t3.47686"){ std::cout << "Hibas teszteset 9" << std::endl; success = false;} //DERIVATE
  getline(sOut, buffer);
  if(buffer != "\t\tInfinite"){ std::cout << "Hibas teszteset 10" << std::endl; success = false;} //INFINITE RESULT
  getline(sOut, buffer);
  if(buffer != "\t\t(2 * (x ^ -1))"){ std::cout << "Hibas teszteset 11" << std::endl; success = false;} //NOT SIMPLIFIED
  getline(sOut, buffer);
  if(buffer != "\t\t-2x^-2"){ std::cout << "Hibas teszteset 12" << std::endl; success = false;} //SIMPLIFIED DERIVATIVE
  getline(sOut, buffer);
  if(buffer != "\t\t2x^-1"){ std::cout << "Hibas teszteset 13" << std::endl; success = false;} //SIMPLIFIED
  getline(sOut, buffer);
  if(buffer != "\t\t"){ std::cout << "Hibas teszteset 14" << std::endl; success = false;} //NOTHING ELSE IS LOGGED
  if(success) std::cout << "\tMinden teszt sikeres!" << std::endl;
}
