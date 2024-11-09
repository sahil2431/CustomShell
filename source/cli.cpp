#include "commands.hpp"
#include "utils.hpp"
#include "dictionary.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits.h>
#include <unistd.h>

#define RED "\033[31m"
#define RESET "\033[0m"
using namespace std;

vector<string> history;

void processCommand(vector<string> args)
{
    if (args[0] == "exit" || args[0] == "e")
    {
        exit(0);
    }
    if (args[0] == "history")
    {
        for (size_t i = 0; i < history.size() - 1; i++)
        {
            cout << i + 1 << ". " << history[i] << endl;
        }
    }
    else
    {

        if (allias.find(args[0]) != allias.end())
        {
            args[0] = allias[args[0]];
        }
        if (commands.find(args[0]) != commands.end())
        {
            if (holds_alternative<CommandNoArgs>(commands[args[0]]))
                get<CommandNoArgs>(commands[args[0]])();
            else
                get<CommandWithArgs>(commands[args[0]])(args);
        }
        else
        {
            cerr << RED << "Command " <<args[0] <<" not found\n"
                 << RESET;
        }
    }
}
void cliLoop()
{
    string input;

    char cwd[PATH_MAX];

    while (true)
    {
        if (getcwd(cwd, sizeof(cwd)) != NULL)
        {
            cout << cwd << "> ";
        }
        else
        {
            cerr << RED << "Error getting current working directory\n"
                 << RESET;
        }

        getline(cin, input);

        if (input.empty())
        {
            continue;
        }

        history.push_back(input);
        vector<string> args = parse_input(input);
        processCommand(args);
    }
}