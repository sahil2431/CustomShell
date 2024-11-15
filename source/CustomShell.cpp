#define _CRT_SECURE_NO_WARNINGS
#include "cli.hpp"
#include<iostream>
#include<string>
#include<vector>

using namespace std;

#define RESET "\033[0m"
#define RED "\033[31m"

int main() {
	const char* user ;
    #ifdef _WIN32
        user = getenv("USERNAME");
    #else
       user = getenv("USER");
    #endif
	if (user == NULL) cout << RED << "Error in getting userName" << RESET << endl;
    cout << "Welcome "<<user<<" to the CLI!\n";
    cliLoop();
    return 0;
}