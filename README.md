# Custom CLI Shell

A custom command-line interface (CLI) shell built in C++ that provides essential command functionalities and a way to manage aliases. This project is designed to run on **Linux** and demonstrates command parsing, alias handling, and modular command organization.

## Features

- **Custom Commands**: Implement and expand CLI commands.
- **Alias Support**: Define and use command aliases for convenience.
- **Modular Design**: Separate files for command functions, command dictionaries, utilities, and main CLI logic.
- **Extensible**: Easily add or modify commands and aliases.


## Getting Started

### Prerequisites

- **Linux OS**: This CLI shell is designed for Linux environments.
- **C++17**: The project uses features from the C++17 standard.
- **Make**: For building the project using the provided `Makefile`.

### Installation

1. **Clone the repository**:

    ```bash
    git clone https://github.com/username/custom-cli-shell.git
    cd custom-cli-shell
    ```

2. **Build the project**:

    ```bash
    make
    ```

3. **Run the CLI**:

    ```bash
    ./my_cli
    ```

### Usage

1. Start the shell by running `./my_cli`.
2. Enter commands as you would in a standard shell.
3. Use defined aliases as shortcuts for complex commands.

### Adding Commands

To add a new command:

1. Define a new function in `commands.cpp`.
2. Declare the function in `commands.h`.
3. Add the command to the `commands` dictionary in `dictionaries.cpp`.

### Example Commands

Below are some sample commands implemented in this project. Expand and modify them as needed:

- `ls`: Lists files in the current directory.
- `cd [path]`: Changes the current directory to the specified path.
- `history`: Shows the history of commands executed in this session.
- `exit`: Exits the custom CLI.

