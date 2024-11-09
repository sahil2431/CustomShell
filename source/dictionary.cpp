#include "dictionary.hpp"
#include "commands.hpp"


std::unordered_map<std::string , std::variant<CommandNoArgs , CommandWithArgs>> commands = {
    {"greet" , greetCommand},
    {"cd" , changeDir},
    {"pwd" , pwdCommand},
    {"ls" , listAlldir},
    {"clear" , clearScreen},
    {"mkdir" , createFolder},
    {"touch" , createFile},
    {"help" , display_help},
    {"rmdir" , removeDir},
    {"rmfile" , removeFile},
    {"echo" , displayMessage},
    {"read" , readFile},
    {"write" , writeFile},
};

std::unordered_map<std::string , std::string> allias = {
    {"dir" , "pwd"},
    {"cdir" , "mkdir"},
    {"cfile" , "touch"},
    {"h" , "help"},
    {"cls" , "clear"},
    {"mdir" , "mkdir"},
    {"mfile" , "touch"},
    {"display" , "echo"}
};