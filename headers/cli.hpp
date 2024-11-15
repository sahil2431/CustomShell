#ifndef CLI_HPP
#define CLI_HPP

#include <string>
#include <vector>

// Function declarations for the CLI
void processCommand(std::vector<std::string>& args, std::vector<std::string>& history);
void cliLoop();

#endif  // CLI_HPP
