#define _CRT_SECURE_NO_WARNINGS
#include "commands.hpp"

#include <iostream>
#include <filesystem>
#include <cstdlib>
#include <fstream>
#include <errno.h> // For errno
#include <cstring> // For strerror

namespace fs = std::filesystem;

#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define RESET "\033[0m"
#define BLUE "\033[34m"

// Function for the greet command (c)
void greetCommand(const vector<string> args)
{
    if (args.size() > 1)
    {
        std::cout << "Hello, " << args[1] << "!\n";
    }
    else
    {
        std::cout << "Hello, user!\n";
    }
}

// Function for the cd command (c)
void changeDir(const std::vector<std::string> args)
{
    if (args.size() < 2)
    {
        cout << RED << "Error: No directory specified\n"
             << RESET;
        return;
    }
    if (args[1] == "~")
    {
        fs::path homeP(getenv("HOMEPATH"));
        fs::current_path(homeP);
        return;
    }
    string inputDir = "";
    for (size_t i = 1; i < args.size(); i++)
    {
        if (i != 1)
            inputDir += " ";
        inputDir += args[i];
    }
    try
    {
        // Get the current working directory as the base reference
        fs::path currentPath = fs::current_path();

        // Handle relative path resolution by resolving it against the current directory
        fs::path targetDir = currentPath / inputDir;

        // Normalize the target path (resolve '..' and '.' correctly)
        targetDir = fs::canonical(targetDir);

        // Check if the directory exists and is indeed a directory
        if (fs::exists(targetDir) && fs::is_directory(targetDir))
        {
            // Change the current directory to the resolved target directory
            fs::current_path(targetDir);
            std::cout << GREEN << "Directory changed successfully to " << targetDir << RESET << std::endl;
        }
        else
        {
            std::cerr << RED << "Error: Directory does not exist or is not a directory" << RESET << std::endl;
        }
    }
    catch (const fs::filesystem_error &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

// Function for the pwd command (c)
void pwdCommand()
{
    std::cout << GREEN << "Current working directory: " << std::filesystem::current_path() << RESET << std::endl;
}

// Function for the clear command (c)
void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Function for the ls command(c)
void listAlldir(const std::vector<std::string> args)
{
    std::string path;
    if (args.size() > 1)
    {
        path = args[1];
    }
    else
    {
        path = std::filesystem::current_path().string();
    }

    if (!std::filesystem::exists(path))
    {
        std::cerr << "Error: Path does not exist.\n";
        return;
    }

    cout << "Listing directories in " << path << "\n";
    try
    {
        for (const auto &entry : std::filesystem::directory_iterator(path))
        {
            cout << entry.path().filename() << "\n";
        }
    }
    catch (const std::filesystem::filesystem_error &e)
    {
        std::cerr << "Filesystem error: " << e.what() << "\n";
    }
}

// Function for the mkdir command (c)
void createFolder(const std::vector<std::string> args)
{
    if (args.size() < 2)
    {
        std::cout << RED << "No directory specified\n"
                  << RESET;
        return;
    }
    for (size_t i = 1; i < args.size(); i++)
    {
        std::filesystem::create_directories(args[i]);
        std::cout << GREEN << "Directory " << BLUE << args[i] << GREEN << " created successfully\n"
                  << RESET;
    }
}

// Function for displaying the message(echo) (c)
void displayMessage(const vector<string> args)
{
    for (size_t i = 1; i < args.size(); i++)
    {
        if (args[i][0] == '$')
        {
            string var = args[i].substr(1);
            const char *envvar = var.c_str();
            const char *value = getenv(envvar);
            if (value == NULL)
            {
                cout << RED << "No environment variable is present of name " << BLUE << envvar << RESET << endl;
            }
            else
            {
                cout << GREEN << var << RESET << " -> " << BLUE << value << RESET << endl;
            }
        }
        else
        {
            std::cout << args[i] << std::endl;
        }
    }
}

// Function for creating files (c)
void createFile(const vector<string> args)
{
    for (string st : args)
    {
        if (st == "touch")
            continue;
        std::ofstream file(st);
        if (!file.is_open())
            cout << RED << "Error in creating the file " << BLUE << st << RESET << endl;
        else
            cout << GREEN << "File " << BLUE << st << GREEN << " created successfully.\n"
                 << RESET;
    }
}

// Function for removing directories (c)
void removeDir(const vector<string> args)
{
    for (size_t i = 1; i < args.size(); i++)
    {
        const char *dir = args[i].c_str();
        try
        {
            if (fs::exists(dir) && fs::is_directory(dir))
            {
                bool has_contents = false;
                for (const auto &entry : fs::directory_iterator(dir))
                {
                    has_contents = true;
                    break; // We found at least one file/subdirectory, exit the loop
                }
                if (has_contents)
                {

                    char c;
                    cout << BLUE << "Directory " << dir << " contains some files. Do you want to continue(Y/N): " << RESET;
                    cin >> c;
                    if (c == 'N' || c == 'n')
                        continue;
                    cin.ignore();
                }
                fs::remove_all(dir);
                cout << GREEN << "Directory " << BLUE << dir << GREEN << " deleted succesfully.\n"
                     << RESET;
            }
            /* code */
        }
        catch (const std::exception &e)
        {
            std::cerr << RED << "Error deleting dirctory: " << dir << " " << e.what() << RESET << '\n';
        }
    }
}

// Function for removing files (c)
void removeFile(const vector<string> args)
{
    for (size_t i = 1; i < args.size(); i++)
    {
        const char *file = args[i].c_str();
        if (remove(file))
        {
            cout << RED << "Error deleting file.\n"
                 << RESET;
        }
        else
        {
            cout << GREEN << "File " << BLUE << file << GREEN << " deleted successfully.\n"
                 << RESET;
        }
    }
}

// Function for reading files (c)
void readFile(const vector<string> args)
{
    if (args.size() < 2)
    {
        cout << RED << "Error: No file name provided.\n"
             << RESET;
        return;
    }
    if (args.size() > 2)
    {
        cout << RED << "Error: Too many arguments.\n"
             << RESET;
        return;
    }
    ifstream file(args[1]);

    if (!file.is_open())
    {
        cout << RED << "Error: File not found.\n"
             << RESET;
        return;
    }

    string line;
    while (getline(file, line))
    {
        cout << line << endl;
    }
    file.close();
}

// Function for writing to files
void writeFile(const vector<string> args)
{
    if (args.size() < 2)
    {
        cout << RED << "Error: No file name provided.\n"
             << RESET;
        return;
    }
    if (args.size() > 2)
    {
        cout << RED << "Error: Too many arguments.\n"
             << RESET;
        return;
    }

    if (fs::exists(args[1]))
    {
        cout << RED << "File is already present. Do you want to overwrite it? (Y/N): " << RESET;
        char c;
        cin >> c;
        cin.ignore();
        if (c == 'N' || c == 'n')
            return;
    }

    ofstream file(args[1]);

    if (!file)
    {
        // File could not be opened, check the error
        char buffer[256];
#ifdef _WIN32
        strerror_s(buffer, sizeof(buffer), errno);
#else
        strerror_r(errno, buffer, sizeof(buffer));
#endif
        cout << RED << "Error: Cannot write to file. Reason: " << buffer << RESET << endl;

        return;
    }
    if (!file.is_open())
    {
        cout << RED << "Error: File not found.\n"
             << RESET;
        return;
    }

    string line;
    cout << YELLOW << "Enter the text to write in the file.\n"
         << RESET;

    while (getline(cin, line))
    {
        // Read each line of input
        if (line.length() == 0)
            break;
        file << line << endl; // Write the line to the file
    }

    file.close();
    cout << GREEN << "File saved successfully." << RESET << endl;
}

// Function for showing environment variables (c)
void showEnvironmentVaribles(const vector<string> args)
{
    if (args.size() > 1)
    {
        const char *envvar = args[1].c_str();
        const char *value = getenv(envvar);
        if (value == NULL)
        {
            cout << RED << "No environment variable is present of name " << BLUE << envvar << RESET << endl;
        }
        else
        {
            cout << GREEN << args[1] << RESET << " -> " << BLUE << value << RESET << endl;
        }
        return;
    }
    extern char **environ;
    std::cout << BLUE << "Environment variables:\n";
    for (char **env = environ; *env != 0; env++)
    {
        char *thisEnv = *env;
        std::cout << thisEnv << std::endl;
    }
    std::cout << RESET;
}

// Function for copying files (c)
void copyFile(const vector<string> args)
{
    if (args.size() < 3)
    {
        cout << RED << "Error: Not enough arguments\n"
             << RESET;
        return;
    }
    try
    {
        fs::path source = args[1];
        fs::path destination = args[2];

        // Check if the source file exists
        if (!fs::exists(source) || !fs::is_regular_file(source))
        {
            cout << RED << "Error: Source file does not exist\n"
                 << RESET;
            return;
        }

        // Check if the destination is a directory
        if (fs::exists(destination) && fs::is_directory(destination))
        {
            destination /= source.filename();
        }
        else if (!fs::exists(destination.parent_path()))
        {
            createFolder({"mkdir", destination.string()});
        }

        fs::copy(source, destination);
        cout << GREEN << "File copied successfully\n"
             << RESET;
    }
    catch (const fs::filesystem_error &e)
    {
        cout << RED << "Error: " << e.what() << RESET << endl;
    }
}

// Function for moving files (c)
void moveFile(const vector<string> args)
{
    if (args.size() < 3)
    {
        cout << RED << "Error: Not enough arguments\n"
             << RESET;
        return;
    }

    try
    {
        fs::path source = args[1];
        fs::path destination = args[2];

        if (!fs::exists(source) || !fs::is_regular_file(source))
        {
            cout << RED << "Error: Source file does not exist\n"
                 << RESET;
            return;
        }
        if (fs::exists(destination) && fs::is_directory(destination))
        {
            destination /= source.filename();
        }
        else if (fs::exists(destination.parent_path()))
        {
            createFolder({"mkdir", destination.string()});
        }

        fs::rename(source, destination);
        cout << GREEN << "File moved successfully\n"
             << RESET;
    }
    catch (fs::filesystem_error &e)
    {
        cout << RED << "Error: " << e.what() << RESET << endl;
    }
}

// Function for help command (c)
void display_help()
{
    cout << GREEN << "Available commands:\n\n";

    cout << "greet [name]                  - Greet a user or show a generic greeting\n";
    cout << "cd <dir>                      - Change directory\n";
    cout << "home or cd ~                  - Go to home directory\n";
    cout << "ls                            - List all directories\n";
    cout << "mkdir or cf <dirnames>        - Create directories\n";
    cout << "touch <fileNames>             - Create files\n";
    cout << "clear or cls                  - Clear the screen\n";
    cout << "pwd                           - Show the current working directory\n";
    cout << "rmdir <dirNames>              - Remove directories\n";
    cout << "rmfile <fileName>             - Remove files\n";
    cout << "echo <message>                - Display message\n";
    cout << "echo <$varName>               - Display environment variable value\n";
    cout << "read <fileName>               - Read file\n";
    cout << "write <fileName>              - Write to file\n";
    cout << "history                       - Show the command history\n";
    cout << "env                           - Show the environment variables\n";
    cout << "env <varName>                 - Show given environment variable value\n";
    cout << "exit                          - Exit the CLI\n";
    cout << "help                          - Show this help message\n"
         << RESET;
}