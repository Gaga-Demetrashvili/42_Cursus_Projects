#!/bin/bash

# Minishell Comprehensive Test Suite
# Tests all builtins, pipes, redirections, environment variables, etc.

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

PASS=0
FAIL=0

echo -e "${BLUE}========================================${NC}"
echo -e "${BLUE}  MINISHELL COMPREHENSIVE TEST SUITE${NC}"
echo -e "${BLUE}========================================${NC}\n"

# Test function
test_cmd() {
    local test_name="$1"
    local cmd="$2"
    local expected_pattern="$3"
    
    echo -n "Testing: $test_name ... "
    
    result=$(echo -e "$cmd\nexit" | ./minishell 2>/dev/null | grep -v "^minishell\$ " | grep -v "^exit$" | sed '/^$/d')
    
    if echo "$result" | grep -q "$expected_pattern"; then
        echo -e "${GREEN}✓ PASS${NC}"
        ((PASS++))
    else
        echo -e "${RED}✗ FAIL${NC}"
        echo -e "  Expected pattern: $expected_pattern"
        echo -e "  Got: $result"
        ((FAIL++))
    fi
}

# Test exit codes
test_exit_code() {
    local test_name="$1"
    local cmd="$2"
    local expected_code="$3"
    
    echo -n "Testing: $test_name ... "
    
    echo -e "$cmd\nexit" | ./minishell 2>/dev/null >/dev/null
    code=$?
    
    if [ $code -eq $expected_code ]; then
        echo -e "${GREEN}✓ PASS${NC}"
        ((PASS++))
    else
        echo -e "${RED}✗ FAIL${NC}"
        echo -e "  Expected exit code: $expected_code"
        echo -e "  Got: $code"
        ((FAIL++))
    fi
}

echo -e "${YELLOW}=== BUILTIN TESTS ===${NC}\n"

# Echo tests
test_cmd "echo simple" "echo hello" "hello"
test_cmd "echo -n flag" "echo -n test" "test"
test_cmd "echo multiple args" "echo hello world 42" "hello world 42"
test_cmd "echo with spaces" "echo    multiple   spaces" "multiple spaces"

# PWD tests
test_cmd "pwd" "pwd" "/home/tbaindur/42_Cursus_Projects/minishell"

# CD tests
echo -n "Testing: cd and pwd ... "
result=$(echo -e "cd /tmp\npwd\nexit" | ./minishell 2>/dev/null | grep -v "^minishell\$ " | grep -v "^exit$" | sed '/^$/d')
if echo "$result" | grep -q "/tmp"; then
    echo -e "${GREEN}✓ PASS${NC}"
    ((PASS++))
else
    echo -e "${RED}✗ FAIL${NC}"
    ((FAIL++))
fi

echo -e "\n${YELLOW}=== ENVIRONMENT VARIABLE TESTS ===${NC}\n"

# Export and env tests
test_cmd "export VAR" "export TEST_VAR=hello\nenv" "TEST_VAR=hello"
test_cmd "export and echo" "export MY_VAR=world\necho \$MY_VAR" "world"
test_cmd "export multiple" "export A=1\nexport B=2\necho \$A \$B" "1 2"

# Unset tests
echo -n "Testing: unset ... "
result=$(echo -e "export TO_UNSET=value\nunset TO_UNSET\nenv\nexit" | ./minishell 2>/dev/null | grep -v "^minishell\$ " | grep -v "^exit$" | grep "TO_UNSET")
if [ -z "$result" ]; then
    echo -e "${GREEN}✓ PASS${NC}"
    ((PASS++))
else
    echo -e "${RED}✗ FAIL${NC}"
    ((FAIL++))
fi

# Exit status test
test_cmd "exit status" "echo test\necho \$?" "0"

echo -e "\n${YELLOW}=== PIPE TESTS ===${NC}\n"

# Simple pipe
test_cmd "simple pipe" "echo hello | cat" "hello"
test_cmd "ls pipe" "ls | head -1" "."

# Multiple arguments with pipe
echo -n "Testing: echo with pipe ... "
result=$(echo -e "echo one two three | cat\nexit" | ./minishell 2>/dev/null | grep -v "minishell\$" | grep -v "^exit$" | sed '/^$/d')
if echo "$result" | grep -q "one two three"; then
    echo -e "${GREEN}✓ PASS${NC}"
    ((PASS++))
else
    echo -e "${RED}✗ FAIL${NC}"
    ((FAIL++))
fi

echo -e "\n${YELLOW}=== REDIRECTION TESTS ===${NC}\n"

# Output redirection
echo -n "Testing: output redirection > ... "
echo -e "echo test_output > /tmp/minishell_test.txt\nexit" | ./minishell 2>/dev/null >/dev/null
if [ -f /tmp/minishell_test.txt ] && grep -q "test_output" /tmp/minishell_test.txt; then
    echo -e "${GREEN}✓ PASS${NC}"
    ((PASS++))
    rm -f /tmp/minishell_test.txt
else
    echo -e "${RED}✗ FAIL${NC}"
    ((FAIL++))
fi

# Append redirection
echo -n "Testing: append redirection >> ... "
echo -e "echo first > /tmp/minishell_append.txt\necho second >> /tmp/minishell_append.txt\nexit" | ./minishell 2>/dev/null >/dev/null
if [ -f /tmp/minishell_append.txt ]; then
    content=$(cat /tmp/minishell_append.txt)
    if echo "$content" | grep -q "first" && echo "$content" | grep -q "second"; then
        echo -e "${GREEN}✓ PASS${NC}"
        ((PASS++))
    else
        echo -e "${RED}✗ FAIL${NC}"
        ((FAIL++))
    fi
    rm -f /tmp/minishell_append.txt
else
    echo -e "${RED}✗ FAIL${NC}"
    ((FAIL++))
fi

# Input redirection
echo -n "Testing: input redirection < ... "
echo "test_input_content" > /tmp/minishell_input.txt
result=$(echo -e "cat < /tmp/minishell_input.txt\nexit" | ./minishell 2>/dev/null | grep -v "minishell\$" | grep -v "^exit$" | sed '/^$/d')
if echo "$result" | grep -q "test_input_content"; then
    echo -e "${GREEN}✓ PASS${NC}"
    ((PASS++))
else
    echo -e "${RED}✗ FAIL${NC}"
    ((FAIL++))
fi
rm -f /tmp/minishell_input.txt

echo -e "\n${YELLOW}=== HEREDOC TESTS ===${NC}\n"

# Heredoc test
echo -n "Testing: heredoc << ... "
result=$(echo -e "cat << EOF\nline1\nline2\nEOF\nexit" | ./minishell 2>/dev/null | grep -v "minishell\$" | grep -v "^exit$" | sed '/^$/d')
if echo "$result" | grep -q "line1" && echo "$result" | grep -q "line2"; then
    echo -e "${GREEN}✓ PASS${NC}"
    ((PASS++))
else
    echo -e "${RED}✗ FAIL${NC}"
    ((FAIL++))
fi

echo -e "\n${YELLOW}=== QUOTE TESTS ===${NC}\n"

# Single quotes
test_cmd "single quotes" "echo 'hello world'" "hello world"
test_cmd "single quotes no expansion" "export VAR=test\necho '\$VAR'" '\$VAR'

# Double quotes
test_cmd "double quotes" 'echo "hello world"' "hello world"
test_cmd "double quotes with expansion" 'export VAR=test\necho "$VAR"' "test"

echo -e "\n${YELLOW}=== EXTERNAL COMMAND TESTS ===${NC}\n"

# Test external commands
test_cmd "external: /bin/ls" "/bin/ls -la" "total"
test_cmd "external: /bin/echo" "/bin/echo test" "test"
test_cmd "PATH resolution: ls" "ls" "Makefile"
test_cmd "PATH resolution: pwd" "pwd" "/home/tbaindur/42_Cursus_Projects/minishell"

echo -e "\n${YELLOW}=== LOGICAL OPERATORS TESTS ===${NC}\n"

# AND operator
test_cmd "AND success" "echo first && echo second" "second"
test_cmd "OR operator" "invalid_cmd || echo fallback" "fallback"

echo -e "\n${YELLOW}=== COMPLEX TESTS ===${NC}\n"

# Complex command
test_cmd "export + echo + pipe" "export COMPLEX=test\necho \$COMPLEX | cat" "test"

# Multiple pipes
echo -n "Testing: multiple pipes ... "
result=$(echo -e "echo one two three | cat | cat\nexit" | ./minishell 2>/dev/null | grep -v "minishell\$" | grep -v "^exit$" | sed '/^$/d')
if echo "$result" | grep -q "one two three"; then
    echo -e "${GREEN}✓ PASS${NC}"
    ((PASS++))
else
    echo -e "${RED}✗ FAIL${NC}"
    ((FAIL++))
fi

echo -e "\n${BLUE}========================================${NC}"
echo -e "${BLUE}           TEST SUMMARY${NC}"
echo -e "${BLUE}========================================${NC}"
echo -e "${GREEN}PASSED: $PASS${NC}"
echo -e "${RED}FAILED: $FAIL${NC}"
echo -e "${BLUE}TOTAL:  $((PASS + FAIL))${NC}"

if [ $FAIL -eq 0 ]; then
    echo -e "\n${GREEN}🎉 ALL TESTS PASSED! 🎉${NC}\n"
    exit 0
else
    echo -e "\n${RED}Some tests failed. Please review.${NC}\n"
    exit 1
fi
