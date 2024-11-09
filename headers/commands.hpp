#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <string> 
#include <vector>  

using namespace std;

void greetCommand(const vector<string> args);
void changeDir(const vector<string> args);
void pwdCommand();
void clearScreen();
void listAlldir(const vector<string> args);
void display_help();
void createFolder(const vector<string> args);
void createFile(const vector<string> args);
void removeDir(const vector<string> args);
void removeFile(const vector<string> args);
void displayMessage(const vector<string> args);
void readFile(const vector<string> args);
void writeFile(const vector<string> args);

#endif