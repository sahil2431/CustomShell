# Custom CLI Shell

A custom command-line interface (CLI) shell built in C++ that provides essential command functionalities and a way to manage aliases. This project is designed to run on **Linux** and **Windows** and demonstrates command parsing, alias handling, and modular command organization.

## Features

- **Custom Commands**: You can create and expand CLI commands easily.
- **Alias Support**: Allows users to use aliases for commonly used commands.
- **Modular Design**: The code is split into different files for ease of maintenance and expansion.
- **Extensibility**: It's simple to add new commands or modify existing ones.
- **Cross-Platform Compatibility**: Works on both **Linux** and **Windows** platforms.

## Getting Started

### Prerequisites

- **Linux** or **Windows OS**: The CLI shell works on both Linux and Windows environments.
- **C++17**: The project uses features from the C++17 standard.
- **CMake**: CMake is used as the build system.

### Installation

1. **Clone the repository**:

    ```bash
    git clone https://github.com/username/custom-cli-shell.git
    cd custom-cli-shell
    ```

2. **Build the project**:

    For **Linux**:

    ```bash
    mkdir build
    cd build
    cmake ..
    make
    ```

    For **Windows** (using Visual Studio):

    ```bash
    mkdir build
    cd build
    cmake .. -G "Visual Studio 16 2019"
    ```

3. **Run the CLI**:

    ```bash
    ./my_cli   # On Linux
    my_cli.exe # On Windows
    ```

### Usage

1. Start the shell by running `./my_cli` (Linux) or `my_cli.exe` (Windows).
2. Enter commands as you would in a standard shell.
3. Use defined aliases for convenience.

### Adding Commands

To add a new command:

1. Define the function in `commands.cpp`.
2. Declare the function in `commands.h`.
3. Add the function to the command dictionary in `dictionaries.cpp`.

---

## Command Summary Table

| Command                                | Description                                           |
|----------------------------------------|-------------------------------------------------------|
| `greet [name]`                         | Greet a user or show a generic greeting               |
| `cd <dir>`                             | Change directory to the specified directory           |
| `home` or `cd ~`                       | Go to the home directory                             |
| `ls`                                    | List all files and directories in the current path   |
| `mkdir` or `cf <dirnames>`             | Create directories with specified names               |
| `touch <fileNames>`                    | Create files with specified names                     |
| `clear` or `cls`                       | Clear the terminal screen                             |
| `pwd`                                   | Show the current working directory                    |
| `rmdir <dirNames>`                     | Remove directories                                   |
| `rmfile <fileName>`                    | Remove files                                         |
| `echo <message>`                       | Display the provided message                          |
| `echo <$varName>`                      | Display the value of the specified environment variable |
| `read <fileName>`                      | Read the content of the specified file                |
| `write <fileName>`                     | Write to the specified file                           |
| `history`                              | Show the command history of the current session       |
| `env`                                  | Show the environment variables                       |
| `calc`                                 | Open a scientific Calculator                          |
| `env <varName>`                        | Show the value of a given environment variable        |
| `exit`                                 | Exit the CLI shell                                    |
| `help`                                 | Show the help message with all available commands     |

---

## Contributing

Contributions to this project are welcome! You can submit issues or pull requests to improve functionality, add more commands, or refine the overall design.

---

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

