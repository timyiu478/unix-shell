#ifndef ProgramRunner_H
#define ProgramRunner_H

#include <vector>
#include <string>
#include <iostream>
#include <filesystem>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

class ProgramRunner {
    private:
      // A vector to store executeable directories
      std::vector<std::string> _executableDirectories;

    public:
      // Constructor
      ProgramRunner(std::vector<std::string> executableDirectories) {
          // Initialize the executable directories from environment variable PATH
          _executableDirectories = executableDirectories;
      }

      // Function to check if a program is in the executable directories
      bool isProgramInPath(const std::string& program);

      // Function to run a program with given arguments
      int runProgram(const std::string& program, const std::vector<std::string>& args);
};

#endif
