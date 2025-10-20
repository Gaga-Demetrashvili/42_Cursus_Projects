#!/bin/bash

# Colors for output
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

echo "=========================================="
echo "    MINISHELL COMPREHENSIVE TEST SUITE"
echo "=========================================="
echo ""

# Function to test a command
test_command() {
    local description="$1"
    local command="$2"
    echo -e "${YELLOW}Testing:${NC} $description"
    echo "Command: $command"
    echo "$command" | timeout 2 ./minishell 2>&1 | head -20
    echo ""
}

# Function to create test files
setup_test_files() {
    echo "Setting up test files..."
    echo "Hello World" > test_input.txt
    echo "Line 1" > test_file1.txt
    echo "Line 2" > test_file2.txt
    echo "Test content" > test_file3.txt
    touch test_empty.txt
    echo ""
}

# Function to cleanup
cleanup() {
    echo "Cleaning up test files..."
    rm -f test_input.txt test_file*.txt test_output.txt test_append.txt test_empty.txt
    rm -f /tmp/test_*
}

# Setup
setup_test_files

echo "=========================================="
echo "1. BASIC COMMANDS"
echo "=========================================="

test_command "Simple echo" "echo hello world"
test_command "Echo with quotes" "echo 'hello world'"
test_command "Echo with double quotes" 'echo "hello world"'
test_command "ls command" "ls"
test_command "pwd command" "pwd"
test_command "whoami command" "whoami"

echo "=========================================="
echo "2. REDIRECTIONS"
echo "=========================================="

test_command "Output redirection" "echo test > test_output.txt"
test_command "Verify output redirection" "cat test_output.txt"
test_command "Append redirection" "echo append >> test_output.txt"
test_command "Verify append" "cat test_output.txt"
test_command "Input redirection" "cat < test_input.txt"
test_command "Input and output redirection" "cat < test_input.txt > test_output.txt"
test_command "Multiple redirections" "cat < test_file1.txt > test_output.txt"

echo "=========================================="
echo "3. PIPES"
echo "=========================================="

test_command "Simple pipe" "echo hello | cat"
test_command "Multiple pipes" "echo hello | cat | cat"
test_command "ls with grep" "ls | grep test"
test_command "Echo with wc" "echo hello world | wc -w"
test_command "Cat with grep" "cat test_input.txt | grep Hello"

echo "=========================================="
echo "4. LOGICAL OPERATORS"
echo "=========================================="

test_command "AND operator (success)" "echo first && echo second"
test_command "AND operator (failure)" "false && echo should_not_print"
test_command "OR operator (failure)" "false || echo should_print"
test_command "OR operator (success)" "true || echo should_not_print"
test_command "Combined AND/OR" "true && echo yes || echo no"

echo "=========================================="
echo "5. HEREDOC"
echo "=========================================="

echo -e "${YELLOW}Testing:${NC} Basic heredoc"
echo "Command: cat << EOF"
(echo "cat << EOF"; echo "line1"; echo "line2"; echo "EOF") | timeout 2 ./minishell 2>&1 | head -10
echo ""

echo -e "${YELLOW}Testing:${NC} Heredoc with pipe"
echo "Command: cat << EOF | grep line"
(echo "cat << EOF | grep line"; echo "line1"; echo "line2"; echo "EOF") | timeout 2 ./minishell 2>&1 | head -10
echo ""

echo "=========================================="
echo "6. EDGE CASES"
echo "=========================================="

test_command "Empty command" ""
test_command "Only spaces" "   "
test_command "Multiple spaces between args" "echo    hello    world"
test_command "Command not found" "nonexistent_command"
test_command "Permission denied (if applicable)" "cat /etc/shadow"
test_command "Empty quotes" "echo ''"
test_command "Mixed quotes" "echo 'hello' world \"test\""

echo "=========================================="
echo "7. COMPLEX COMBINATIONS"
echo "=========================================="

test_command "Pipe with redirection" "cat test_input.txt | grep Hello > test_output.txt"
test_command "Multiple pipes with redirection" "echo test | cat | cat > test_output.txt"
test_command "AND with pipe" "true && echo success | cat"
test_command "OR with pipe" "false || echo fallback | cat"
test_command "Redirection after pipe" "echo test | cat > test_output.txt"

echo "=========================================="
echo "8. ENVIRONMENT VARIABLES (if implemented)"
echo "=========================================="

test_command "Echo PATH" "echo \$PATH"
test_command "Echo HOME" "echo \$HOME"
test_command "Echo USER" "echo \$USER"
test_command "Echo exit status" "echo \$?"

echo "=========================================="
echo "9. WILDCARDS (if implemented)"
echo "=========================================="

test_command "Wildcard expansion" "echo test_file*.txt"
test_command "Wildcard with command" "ls test_file*.txt"
test_command "Multiple wildcards" "echo *.txt"

echo "=========================================="
echo "10. STRESS TESTS"
echo "=========================================="

test_command "Very long pipe chain" "echo a | cat | cat | cat | cat | cat"
test_command "Many arguments" "echo 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15"
test_command "Long string" "echo 'this is a very long string that should work fine even with many words'"

echo "=========================================="
echo "11. ERROR HANDLING"
echo "=========================================="

test_command "Unclosed quote (single)" "echo 'unclosed"
test_command "Unclosed quote (double)" 'echo "unclosed'
test_command "Invalid pipe at start" "| cat"
test_command "Invalid pipe at end" "echo test |"
test_command "Double pipe" "echo test || cat"
test_command "Redirection without file" "cat >"
test_command "Invalid redirection" "cat < nonexistent.txt"

echo "=========================================="
echo "12. SPECIAL CHARACTERS"
echo "=========================================="

test_command "Dollar sign" "echo \$"
test_command "Semicolon (if supported)" "echo hello; echo world"
test_command "Parentheses (if supported)" "echo (test)"
test_command "Backslash" "echo \\"
test_command "Asterisk" "echo *"

echo "=========================================="
echo "TEST SUITE COMPLETE"
echo "=========================================="

# Cleanup
cleanup

echo -e "${GREEN}All tests executed!${NC}"
echo "Please review the output above for any errors or unexpected behavior."
