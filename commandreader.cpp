#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
#include "memtrace.h"
#include "operand.h"
#include "commandreader.h"

void CommandReader::readCommand(std::istream& is){
  getline(is, commandString);
  pos = commandString.find(':');
}
bool CommandReader::setExpression(){
  if(pos == -1)
    return false;
  deleteWhiteSpaces(commandString.substr(pos + 1));
  commandString = commandString.substr(0, pos);
  return true;
}

bool CommandReader::getCommand(std::string& str){
    a = b = "";
    std::stringstream ss;
    ss << commandString;
    ss >> str >> a >> b;
    return a != "";
}
void CommandReader::deleteWhiteSpaces(const std::string& str){
  char* expr = new char[str.length() + 1];
  const char* wws = str.c_str();
  size_t l = str.length();
  size_t j = 0;
  for (size_t i = 0; i < l; i++)
    if(str[i] != ' ') expr[j++] = wws[i];
  expr[j] = '\0';
  expression = string(expr);
  delete[] expr;
}
