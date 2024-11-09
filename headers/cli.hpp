#ifndef CLI_HPP
#define CLI_HPP

#include <string>
#include <vector>

// Function declarations for the CLI
void cliLoop();
void processCommand(const std::vector<std::string>& args, std::vector<std::string>& history);

#endif  // CLI_HPP
