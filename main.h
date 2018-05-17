#ifndef MAIN_HEADER
#define MAIN_HEADER
#include <iostream>
#include "memtrace.h"
#include "interpreter.h"
#include "count.h"
#include "derivater.h"
#include "integrater.h"
#include "logger.h"
#include "derivative.h"
#include "exit.h"
#include "commandreader.h"

class Main{
private:
  Calculator* calculator; //stores an actual calculator
  std::string command; //stores the command
  CommandReader* cmd; //stores a CommandReader object
  bool executeCommands(const std::string& command){ //decides which calculator shall be used
    if(command == "count")
      calculator = new Count();
    else if(command == "derivate")
      calculator = new Derivater();
    else if(command == "integrate")
      calculator = new Integrater();
    else if(command == "write")
      calculator = new Logger();
    else if(command == "derivative")
      calculator = new Derivative();
    else if(command == "exit"){
      calculator = new Exit();
      return false;
    }
    else
      throw "Invalid command";
    return true;
  }
public:
  Main(): calculator(new Interpreter("0")), cmd(new CommandReader()){
    std::cout << "\tWelcome to The Calculator!\n\n";
    std::cout << "\tYou can type 5 calculating commands:\n";
    std::cout << "\t\"count\" with an optional parameter, to calculate result with substituting the given parameter\n";
    std::cout << "\t\"derivate\" with an optional parameter, to get the value of the derivative in the given point\n";
    std::cout << "\t\"integrate\" with 2 optional parameters, to get the value of the integrated function in the given intervall\n";
    std::cout << "\t\"write\" without any parameters, to log the current expression with the clear operation ranking\n";
    std::cout << "\t\"derivative\" without any parameters, to get the whole derivated function\n\n";
    std::cout << "\tThe default expression and parameters are constant zeros.\n";
    std::cout << "\tIf you want to change the expression that you're executing your commands on, type \':\' after your command, and add your new expression.\n";
    std::cout << "\tIn order to exit, type \"exit\"\n\n";
    std::cout << "\tExample: \n";
    std::cout << "\twrite: pow(x, 2)\n";
    std::cout << "\tx ^ 2\n";
    std::cout << "\tderivative\n";
    std::cout << "\t2x\n\n";
    std::cout << "\tHave fun" <<std::endl;
    calculator->execute();
  }
  void readCommands(std::istream& is = std::cin, std::ostream& os = std::cout){
    bool b = true;
    while(b){ //infinte loop for reading commands
      if(calculator){
        delete calculator;    //reseting calculator (the previous operation is static, so it's still stored)
        calculator = nullptr;
      }
      os << '\t';
      cmd->readCommand(is);     //reads new calculating command
      if(cmd->setExpression()){ //if a new methemtical expression was added, it shall be interpreted to the abstract tree
        try{
          calculator = new Interpreter(cmd->expression);
          calculator->execute();
          delete calculator;
          calculator = nullptr;
        }
        catch(std::invalid_argument err){
          os << '\t' << err.what() << std::endl;
          delete calculator;
          calculator = new Interpreter("0"); //If interpretation failed, constant zero is added to the abstract tree
          calculator->execute();
          delete calculator;
          calculator = nullptr;
          continue;
        }
      }
      if(cmd->getCommand(command)){ //gets command, and if parameters were found (return value of getCommand) they are set
        try{
          b = executeCommands(command);//executeCommands return false if the called command was exit, the infinite loop stops
          calculator->setOperands(cmd->a, cmd->b);
        }
        catch(const char* str){ os << '\t' << str << std::endl; continue; }
      }
      else{
        try{
          b = executeCommands(command);//executeCommands return false if the called command was exit, the infinite loop stops
        }
        catch(const char* str){ os << '\t' << str << std::endl; continue;}
      }
      try{
        calculator->execute(); //calculation starts, the resultString will be prepared
        os << '\t' << calculator->getResult() << std::endl; // getResult returns the formatted result of the calculation
      }
      catch(...){ os << "\tError occured" << std::endl; continue;}
    }
  }
  ~Main(){ delete calculator; delete cmd; }
};

#endif
