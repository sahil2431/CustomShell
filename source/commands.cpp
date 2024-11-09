#include "commands.hpp"
#include <iostream>
#include <vector>
#include <limits.h>   // For PATH_MAX
#include <filesystem> // For directory listing
#include <unistd.h>   // for chdir() , getcwd() , fork(), execvp()
#include <cstring>    // For strerror()
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h> // for access
#include <sys/types.h>
#include <fstream>


using namespace std;
namespace fs = filesystem;

#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define RESET "\033[0m"
#define BLUE "\033[34m"

// Greet the user
void greetCommand(const vector<string> args)
{
    if (args.size() > 1)
    {
        cout << "Hello, " << args[1] << "!\n";
    }
    else
    {
        cout << "Hello, user!\n";
    }
}

// Change the current working directory
void changeDir(const vector<string> args) {
    string inputDir = "";
    for(size_t i=1; i<args.size() ; i++) {
        if(i != 1) inputDir += " ";
        inputDir += args[i];
    }
    try {
        // Get the current working directory as the base reference
        fs::path currentPath = fs::current_path(); 

        // Handle relative path resolution by resolving it against the current directory
        fs::path targetDir = currentPath / inputDir; 

        // Normalize the target path (resolve '..' and '.' correctly)
        targetDir = fs::canonical(targetDir);  

        // Check if the directory exists and is indeed a directory
        if (fs::exists(targetDir) && fs::is_directory(targetDir)) {
            // Change the current directory to the resolved target directory
            fs::current_path(targetDir);
            std::cout << GREEN << "Directory changed successfully to " << targetDir << RESET<<std::endl;
        } else {
            std::cerr <<RED<< "Error: Directory does not exist or is not a directory" << RESET<<std::endl;
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

// Print the current working directory
void pwdCommand()
{
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        cout << BLUE << "Current working directory: " << cwd << RESET << "\n";
    }
    else
    {
        cerr << RED << "Error getting current working directory\n"
             << RESET;
    }
}

// List all directories
void listAlldir(const vector<string> args)
{
    for (string s : args)
        cout << s << endl;
    char path[PATH_MAX];
    if (args.size() > 1)
    {
        strcpy(path, args[1].c_str());
    }
    else
    {
        if (getcwd(path, sizeof(path)) == NULL)
        {
            cerr << RED << "Error getting current working directory\n"
                 << RESET;
            return;
        }
    }
    cout << GREEN << "Listing directories in " << path << RESET << "\n";
    for (const auto &entry : fs::directory_iterator(path))
    {
        cout << entry.path().filename() << "\n";
    }
}

// Clear the screen
void clearScreen()
{
    system("clear");
}

void createFolder(const vector<string> args) {
    for(string st : args) {
        if(st == "cf" || st == "mkdir") continue;
        const char* folder = st.c_str();
        if(mkdir(folder , 0755)) cout<<RED<<"Error in creating directory "<<folder<<RESET<<endl;
    }

}

void createFile(const vector<string> args) {
    for(string st : args) {
        if(st == "touch") continue;
        ofstream file(st);
        if(!file.is_open()) cout<<RED <<"Error in creating the file "<<BLUE<<st<<RESET<<endl;
    }
}

void removeDir(const vector<string> args) {
    for(size_t i = 1 ; i<args.size() ; i++) {
        const char* dir = args[i].c_str();
        try
        {
        if(fs::exists(dir) && fs::is_directory(dir)) {
            bool has_contents = false;
            for (const auto& entry : fs::directory_iterator(dir)) {
                has_contents = true;
                break;  // We found at least one file/subdirectory, exit the loop
            }
            if(has_contents) {

              char c;
            cout<<BLUE<< "Directory "<<dir<<" contains some files. Do you want to continue(Y/N): "<<RESET;
            cin>>c;
            if(c == 'N' || c == 'n') continue;
            }
            fs::remove_all(dir);
            cout<<GREEN<<"Directory "<<dir<<" deleted succesfully.\n"<<RESET;
        }
            /* code */
        }
        catch(const std::exception& e)
        {
            std::cerr <<RED<<"Error deleting dirctory: "<<dir<<" "<< e.what() << RESET<<'\n';
        }
        
    }
}

void removeFile(const vector<string> args) {
    for(size_t i  = 1 ; i<args.size() ; i++) {
        const char* file = args[i].c_str();
        if(remove(file)) {
            cout <<RED<<"Error deleting file.\n"<<RESET;
        }else {
            cout<<GREEN<<"File " <<file<<" deleted successfully.\n"<<RESET;
        }
    }
}

void displayMessage(const vector<string> args) {
    for(size_t i = 1 ;i<args.size() ; i++) {
        cout <<args[i]<<endl;
    }
}

void readFile(const vector<string> args) {
    if(args.size() < 2) {
        cout<<RED<<"Error: No file name provided.\n"<<RESET;
        return;
    }
    if(args.size() > 2) {
        cout<<RED<<"Error: Too many arguments.\n"<<RESET;
        return;
    }
    ifstream file(args[1]);

    if(!file.is_open()) {
        cout<<RED<<"Error: File not found.\n"<<RESET;
        return;
    }

    string line;
    while(getline(file , line)) {
        cout<<line<<endl;
    }
    file.close();
}

void writeFile(const vector<string> args) {
    if(args.size() < 2) {
        cout<<RED<<"Error: No file name provided.\n"<<RESET;
        return;
    }
    if(args.size() > 2) {
        cout<<RED<<"Error: Too many arguments.\n"<<RESET;
        return;
    }

    ofstream file(args[1]);
    if (!file) {
        // File could not be opened, check the error
        cout << "Error: Cannot write to file. Reason: " << strerror(errno) << endl;
        return;
    }
    if(!file.is_open()) {
        cout<<RED<<"Error: File not found.\n"<<RESET;
        return;
    }

    string line;
    cout<<YELLOW<<"Enter the text to write in the file.\n"<<RESET;

    while (getline(cin , line)) {
        // Read each line of input
        if(line.length() == 0) break;
        file << line << endl;  // Write the line to the file
    }
    

    file.close();
    cout << GREEN << "File saved successfully." << RESET << endl;

}
// Display the help message
void display_help()
{
    cout << GREEN << "Available commands:\n";
    cout << "greet [name]            - Greet a user or show a generic greeting\n";
    cout << "cd <dir>                - Change directory\n";
    cout << "ls                      - List all directories\n";
    cout << "mkdir or cf <dirnames>  -Create directories\n"; 
    cout <<"touch <fileNames>        -Create files\n";
    cout << "clear or cls            - Clear the screen\n";
    cout << "pwd                     - Show the current working directory\n";
    cout << "rmdir <dirNames>        -Remove directories\n";
    cout << "rmfile <fileName>       -Remove files\n";
    cout << "echo <message>          -Display message\n";
    cout << "read <fileName>         -Read file\n";
    cout << "write <fileName>        -Write to file\n";
    cout << "history                 - Show the command history\n";
    cout << "exit                    - Exit the CLI\n";

    cout << "help           - Show this help message\n"
              << RESET;
}