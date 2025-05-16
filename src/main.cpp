#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include "builtinCommands.hpp"
#include "programRunner.hpp"

int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  // Get the PATH environment variable
  char* pathEnv = std::getenv("PATH");
  std::vector<std::string> executableDirectories = {}; 

  // Split the PATH environment variable into directories
  if (pathEnv != nullptr) {
    std::string path(pathEnv);
    size_t pos = 0;
    while ((pos = path.find(':')) != std::string::npos) {
      executableDirectories.push_back(path.substr(0, pos));
      path.erase(0, pos + 1);
    }
    executableDirectories.push_back(path);
  }


  // Initialize the BuiltinCommands object
  BuiltinCommands builtinCommands = BuiltinCommands(executableDirectories);
  // Initialize the ProgramRunner object
  ProgramRunner programRunner = ProgramRunner(executableDirectories);

  // Read Eval Print Loop
  while (true) { 
    std::cout << "$ ";

    std::string input;
    std::getline(std::cin, input);

    // Check if the input is builtin command
    if (builtinCommands.isBuiltinCommand(input.substr(0, input.find(' ')))) {
      // Split the input into command and arguments
      std::vector<std::string> args;
      size_t pos = 0;
      while ((pos = input.find(' ')) != std::string::npos) {
        args.push_back(input.substr(0, pos));
        input.erase(0, pos + 1);
      }
      args.push_back(input);

      // Execute the builtin command
      builtinCommands.executeCommand(args[0], args);
    } else {
      if (programRunner.isProgramInPath(input.substr(0, input.find(' ')))) {
        // Split the input into command and arguments
        std::vector<std::string> args;
        size_t pos = 0;
        while ((pos = input.find(' ')) != std::string::npos) {
          args.push_back(input.substr(0, pos));
          input.erase(0, pos + 1);
        }
        args.push_back(input);

        // Run the program
        programRunner.runProgram(args[0], args);
          
      } else {
        std::cout << input << ": command not found" << std::endl;
      }
    }
  }
}
