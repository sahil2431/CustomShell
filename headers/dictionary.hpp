#ifndef DICTIOANRY_HPP
#define DICTIOANRY_HPP

#include <unordered_map>
#include <string>
#include <functional>
#include <vector>
#include <variant>

using CommandNoArgs = std::function<void()>;
using CommandWithArgs = std::function<void(const std::vector<std::string>)>;

//Dictionary of all the commands
extern std::unordered_map<std::string, std::variant<CommandNoArgs, CommandWithArgs>> commands;

//Dictionary of all the allias
extern std::unordered_map<std::string, std::string> allias;

#endif