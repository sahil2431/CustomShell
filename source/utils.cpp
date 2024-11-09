#include "utils.hpp"
#include <iostream>
#include <sstream>

using namespace std;

vector<string> parse_input(const string &input)
{
    vector<string> args;
    istringstream iss(input);
    string arg = "";
    bool invertedComma = false;
    for (char c : input)
    {
        if(c == '"') invertedComma = !invertedComma;
        else if (!invertedComma && c == ' ')
        {
            args.push_back(arg);
            arg = "";
        }
        else arg += c;
    }
    args.push_back(arg);
    arg = "";

    return args;
}