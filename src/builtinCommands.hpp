#ifndef BuiltinCommands_H
#define BuiltinCommands_H

#include <vector>
#include <iostream>
#include <filesystem>
#include <string>
#include <unordered_map>

class BuiltinCommands {
  private:
    // A vector to store executeable directories
    std::vector<std::string> _executableDirectories;

    // hash map to store builtin commands
    std::unordered_map<std::string, void (BuiltinCommands::*)(const std::vector<std::string>&)> _commandMap = {};

    // Function to handle the 'exit' command: exit the shell with a given status
    void exit(const std::vector<std::string>& args);

    // Function to handle the 'echo' command: print arguments to stdout
    void echo(const std::vector<std::string>& args);

    // Function to handle the 'type; command: print how a command would be interpreted if used
    void type(const std::vector<std::string>& args);

  public:
    // constructor
    BuiltinCommands(std::vector<std::string> executableDirectories) {
        // Initialize the executable directories from environment variable PATH
        _executableDirectories = executableDirectories;

        // Initialize the command map with builtin commands
        _commandMap["exit"] = &BuiltinCommands::exit;
        _commandMap["echo"] = &BuiltinCommands::echo;
        _commandMap["type"] = &BuiltinCommands::type;
    }

    // Check if a command is a builtin command
    bool isBuiltinCommand(const std::string& command);

    // Function to execute a builtin command
    void executeCommand(const std::string& command, const std::vector<std::string>& args);
};

#endif
