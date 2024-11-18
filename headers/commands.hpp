#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <string> 
#include <vector>  

using namespace std;

void greetCommand(const vector<string> args); //w
void changeDir(const vector<string> args); //w
void pwdCommand(); //w
void clearScreen(); //w
void listAlldir(const vector<string> args); //w
void display_help(); //w
void displayMessage(const vector<string> args); //w


void createFolder(const vector<string> args);//w
void createFile(const vector<string> args);//w
void removeDir(const vector<string> args); //w 
void removeFile(const vector<string> args);//w
void readFile(const vector<string> args); //w
void writeFile(const vector<string> args); //w
void copyFile(const vector<string> args); //w
void moveFile(const vector<string> args); //w(if distination is not present then it renames the file with dir name)

void editFile(const vector<string> args);

void showEnvironmentVaribles(const vector<string> args);


#endif