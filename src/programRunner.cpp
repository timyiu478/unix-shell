#include "programRunner.hpp"

bool ProgramRunner::isProgramInPath(const std::string& program) {
  // Check if the program is in the executable directories
  for (const auto& dir : _executableDirectories) {
      std::string path = dir + "/" + program;
      if (std::filesystem::exists(path)) {
          return true;
      }
  }
  return false;
}

int ProgramRunner::runProgram(const std::string& program, const std::vector<std::string>& args) {
  // Check if the program is in the executable directories
  for (const auto& dir : _executableDirectories) {
      std::string path = dir + "/" + program;
      if (std::filesystem::exists(path)) {
          // Fork the process
          pid_t pid = fork();

          // Check if fork was successful
          if (pid < 0) {
              std::cerr << "Fork failed" << std::endl;
              return 1;
          } // execute the program in the child process
          else if (pid == 0) {
              // Convert args to char* array
              std::vector<char*> c_args;
              for (const auto& arg : args) {
                  c_args.push_back(const_cast<char*>(arg.c_str()));
              }
              c_args.push_back(nullptr); // Null-terminate the array

              // Execute the program
              execv(path.c_str(), c_args.data());

              // If execv fails, print an error message
              std::cerr << "Exec failed" << std::endl;
              return 1;
          } 

          // Parent process: wait for the child process to finish
          int status;
          waitpid(pid, &status, 0);

          return status;
      }
  }
  std::cerr << program << ": command not found" << std::endl;
}
