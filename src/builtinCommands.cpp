#include "builtinCommands.hpp"

void BuiltinCommands::exit(const std::vector<std::string>& args) {
    if (args.size() != 2) {
        std::cerr << "Usage: exit <status>" << std::endl;
        return;
    } else {
        std::exit(std::stoi(args[1]));
    }
}

void BuiltinCommands::echo(const std::vector<std::string>& args) {
    for (size_t i = 1; i < args.size(); ++i) {
        std::cout << args[i] << " ";
    }
    std::cout << std::endl;
}

void BuiltinCommands::type(const std::vector<std::string>& args) {
    if (args.size() != 2) {
        std::cerr << "Usage: type <command>" << std::endl;
        return;
    }
    // Check if the command is a builtin command
    if (isBuiltinCommand(args[1])) {
        std::cout << args[1] << " is a shell builtin" << std::endl;
        return;
    }
    // Check if the command is an executable in the PATH directories
    for (const auto& dir : _executableDirectories) {
        std::string path = dir + "/" + args[1];
        if (std::filesystem::exists(path)) {
            std::cout << args[1] << " is " << path << std::endl;
            return;
        }
    }
    // If the command is not found in the PATH directories and is not a builtin command
    std::cout << args[1] << ": not found" << std::endl;
}

bool BuiltinCommands::isBuiltinCommand(const std::string& command) {
    return _commandMap.find(command) != _commandMap.end();
}

void BuiltinCommands::executeCommand(const std::string& command, const std::vector<std::string>& args) {
    auto it = _commandMap.find(command);
    if (it != _commandMap.end()) {
        (this->*(it->second))(args);
    } else {
        std::cout << "Command not found: " << command << std::endl;
    }
}
