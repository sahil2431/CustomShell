#include "cli.hpp"
#include "dictionary.hpp"
#include "utils.hpp"

#include <iostream>

#include <vector>
#include <filesystem>
#include <sstream>
#include <cstring>
#include <sstream>

#define RED "\033[31m"
#define RESET "\033[0m"

char* getCurrentDirectory() {
	std::string path = std::filesystem::current_path().string();
	char* cstr = new char[path.length() + 1];
	//for windows use strcpy_s and for linux use strcpy
	#ifdef _WIN32
		strcpy_s(cstr, path.length() + 1, path.c_str());
	#else
		strcpy(cstr, path.c_str());
	#endif
	return cstr;
}


//static/* char* getCurrentUser() {
//	char* user = nullptr;
//	size_t len;
//	_dupenv_s(&user, &len, "USER");
//	return user;
//}*/


void processCommand(std::vector<std::string>& args, std::vector<std::string>& history) {
	if (args.empty()) {
		std::cout <<RED<< "No command entered\n"<<RESET;
		return;
	}
	if (args[0] == "exit") {
		std::cout<<RED<<"Exiting CLI"<<RESET<<std::endl;
		exit(0);
	}
	else if (args[0] == "history") {
		for (size_t i = 0 ; i<history.size()-1 ;i++ ) {
			std::cout << history[i] << std::endl;
		}
	} 
	else {
		if (allias.find(args[0]) != allias.end()) {
			args[0] = allias[args[0]];
		}
		if (commands.find(args[0]) != commands.end()) {
			if (std::holds_alternative<CommandNoArgs>(commands[args[0]])) {
				std::get<CommandNoArgs>(commands[args[0]])();
			}
			else {
				std::get<CommandWithArgs>(commands[args[0]])(args);
			}
		}
		else {
			std::string commmand ;
			for(auto i : args) {
				commmand += i + " ";
			}

			system(commmand.c_str());
		}
	}
}

void cliLoop() {

	std::string input;
	std::vector<std::string> history;
	while (true) {
		std::cout <<"@CLI: " << getCurrentDirectory() << ">";
		std::getline(std::cin, input);

		if (input.length() == 0) continue;
		history.push_back(input);
		if (allias.find(input) != allias.end()) {
			input = allias[input];
		}
		std::vector<std::string> args = parse_input(input);
		processCommand(args, history);
	}
}