# Minishell

## Table of Contents
- [Introduction](#introduction)
- [Project Structure](#project-structure)
- [Installation and Usage](#installation-and-usage)
- [Features](#features)
- [Skills Learnt](#skills-learnt)
- [Contributing](#contributing)
- [Requirements](#requirements)

## Introduction
Minishell is a group project developed for 42 School that aims to create a simple Unix shell. It provides basic command-line functionality, including executing commands, handling environment variables, and managing redirections.


## Installation
To install and run the Minishell project, follow these steps:

1. Clone the repository:
   ```sh
   git clone https://github.com/yourusername/minishell.git
   cd minishell
   
   ```
2. Compile:
   ```sh
   make
    
   ```
3. Run program:

    After compiling the project, you can run the Minishell executable to start the shell.
    ```sh
    ./minishell  
    ```
    It supports basic Unix commands and features like environment variables and redirections. This is a basic example of how to use the program, but the possibilities are almost infinite!
    ```sh
    ./minishell
    ls -l | wc
    echo $?
    exit 2
    ```

## Features
* **Command Execution:** Supports executing external commands and built-in shell commands.
* **Redirections:** Handles input (<), output (>), and append (>>) redirections.
* **Pipelines:** Allows chaining commands using pipes (|).
* **Environment Variables:** Manages shell environment variables and supports variable expansion.
* **Built-in Commands:** Implements built-in commands such as echo, cd, pwd, env, export, unset, and exit.
* **Signal Handling:** Handles signals like Ctrl+C (SIGINT) and Ctrl+\ (SIGQUIT) gracefully.
* **Error Handling:** Provides informative error messages for command execution failures and syntax errors.
* **History:** Stores command history and supports navigating through it using arrow keys and history command.
* **Customizable Prompt:** Allows customization of the shell prompt using environment variables.
* **Scripting:** Supports running shell scripts (sh files) and executing multiple commands from a file.
* **File Permissions:** Enforces file permissions and access control for commands and files.

## Skills Learned and Developed
* **Shell Programming:** Developing a basic Unix shell with command parsing and execution.
* **Process Management:** Handling processes and executing commands using system calls.
* **File I/O Operations:** Implementing input/output redirections.
* **Collaborative Development:** Contributing to a group project and integrating individual components like command execution.

## Contributing
This project was developed collaboratively. My specific contribution focused on the execution part (including built-in commands), ensuring commands are executed correctly within the shell environment. Additionally I also worked on expandables and environment varibales.

## Requirements
* GCC or Clang compiler.
* Make utility.
