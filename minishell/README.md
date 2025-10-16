# Minishell - 42 Project

A simple shell implementation in C, following the 42 school norms (norminette).

## 📁 Project Structure

```
minishell/
├── include/                    # Header files
│   ├── minishell_types.h      # Main type definitions and function prototypes
│   └── ft_gb_collect.h        # Garbage collector header
│
├── src/                        # Source files
│   ├── parsing/               # Parsing module
│   │   ├── parse.c           # Main parser entry point
│   │   ├── parse_utils.c     # Parser utility functions (argv building)
│   │   ├── parse_redirections.c  # Redirection handling
│   │   └── create_nodes.c    # AST node creation
│   │
│   ├── execution/             # Execution module
│   │   ├── execute.c         # Main execution dispatcher
│   │   ├── execute_command.c # Simple command execution
│   │   ├── execute_pipe.c    # Pipeline execution
│   │   └── execute_heredoc.c # Heredoc handling
│   │
│   ├── tokenization/          # Tokenization & expansion module
│   │   ├── tokenizer.c       # Lexical analysis
│   │   ├── token_utils.c     # Token utility functions
│   │   ├── expand.c          # Variable expansion
│   │   └── wildcards_handler.c  # Wildcard pattern matching
│   │
│   └── utils/                 # Utility functions
│       ├── ft_gb_collect.c   # Garbage collector implementation
│       └── debugging_helpers.c  # Debug printing functions
│
├── obj/                       # Object files (generated during compilation)
│   ├── parsing/
│   ├── execution/
│   ├── tokenization/
│   └── utils/
│
├── minishell.c               # Main entry point
├── Makefile                  # Build configuration
└── README.md                 # This file
```

## 🔧 Compilation

```bash
make        # Compile the project
make clean  # Remove object files
make fclean # Remove object files and executable
make re     # Rebuild from scratch
```

## 📚 Module Description

### Parsing Module (`src/parsing/`)
Handles the transformation of tokens into an Abstract Syntax Tree (AST).

- **parse.c**: Main parser with support for pipes, AND/OR operators, and parentheses
- **parse_utils.c**: Helper functions for building command arguments
- **parse_redirections.c**: Handles input/output redirections (<, >, >>, <<)
- **create_nodes.c**: Creates AST nodes (command, pipe, AND, OR)

### Execution Module (`src/execution/`)
Executes the AST by forking processes and managing pipes.

- **execute.c**: Main dispatcher for different node types (AND, OR, PIPE, COMMAND)
- **execute_command.c**: Executes simple commands with redirections
- **execute_pipe.c**: Handles pipeline execution (cmd1 | cmd2)
- **execute_heredoc.c**: Manages here-documents (<<)

### Tokenization Module (`src/tokenization/`)
Breaks input into tokens and expands variables/wildcards.

- **tokenizer.c**: Lexical analysis (splits input into tokens)
- **token_utils.c**: Token manipulation utilities
- **expand.c**: Variable expansion ($VAR, $?)
- **wildcards_handler.c**: Wildcard pattern matching (*)

### Utils Module (`src/utils/`)
General utility functions.

- **ft_gb_collect.c**: Custom garbage collector for memory management
- **debugging_helpers.c**: Functions to print AST and token lists for debugging

## 🎯 Features

- Command execution with absolute and relative paths
- Pipes (`|`)
- Logical operators (`&&`, `||`)
- Redirections (`<`, `>`, `>>`, `<<`)
- Variable expansion (`$VAR`, `$?`)
- Wildcard expansion (`*`)
- Subshells with parentheses `()`
- Signal handling (Ctrl+C, Ctrl+D, Ctrl+\\)

## 📝 Norminette Compliance

All files follow the 42 school norms:
- Maximum 25 lines per function
- Maximum 5 functions per file
- Maximum 5 variables per function
- Maximum 4 parameters per function
- No forbidden control structures (for, do-while, switch with multiple cases)
- Proper indentation (tabs)
- Comments removed from function scope

## 🔍 Code Organization Principles

1. **Separation of Concerns**: Each module handles a specific aspect (parsing, execution, tokenization)
2. **Single Responsibility**: Functions are kept small and focused
3. **Modularity**: Easy to test and maintain individual components
4. **Readability**: Clear naming conventions and logical file grouping

## 👥 Authors

- gdemetra (GitHub: @gdemetra)

## 📄 License

This project is part of the 42 school curriculum.
