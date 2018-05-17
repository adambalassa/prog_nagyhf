#ifndef COMMANDREADER_HEADER
#define COMMANDREADER_HEADER
#include <iostream>
#include <string>
#include "memtrace.h"
using std::string;
class CommandReader{
  int pos;
  void deleteWhiteSpaces(const std::string&); //deletes all unnecessary whitespaces
  std::string commandString; //stores the whole command
public:
  std::string expression; //stores the mathematical expression
  std::string a, b; //stores the parameters
  CommandReader(): pos(0), commandString(""), a(""), b(""){}
  bool setExpression(); //cuts the commandstring to set the Expression, returns true, if expression was found
  bool getCommand(std::string&); //gets the command and sets the parameters. returns true if parameters were found
  void readCommand(std::istream&); //reads a new command from standard input
  virtual ~CommandReader(){}
};
#endif
