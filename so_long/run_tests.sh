#!/bin/bash

# Path to your compiled so_long executable
GAME="./so_long"

# Path to your test maps
TEST_DIR="./maps/test"

# Color helpers
GREEN="\e[32m"
RED="\e[31m"
RESET="\e[0m"

# Exit if game not compiled
if [ ! -f "$GAME" ]; then
    echo -e "${RED}Error:${RESET} so_long executable not found. Compile it first!"
    exit 1
fi

echo "Running validation tests..."

first=1

# Loop through all .ber files in tests folder (recursively)
find "$TEST_DIR" -name "*.ber" | while read -r mapfile; do
    echo "Testing: $mapfile"

   if [ $first -eq 1 ]; then
        # First iteration: overwrite files with header only
        echo -e "=== Testing $mapfile ===\n" > output.log
        echo -e "=== Testing $mapfile ===\n" > valgrind.log
        first=0
    else
        # Subsequent iterations: append with leading blank line and header
        echo -e "\n=== Testing $mapfile ===\n" >> output.log
        echo -e "\n=== Testing $mapfile ===\n" >> valgrind.log
    fi

    # Run with Valgrind and capture output
    valgrind --leak-check=full --show-leak-kinds=all --error-exitcode=42 "$GAME" "$mapfile" >> output.log 2>> valgrind.log
    EXIT_CODE=$?

    # Check program exit code for validation
    if [ $EXIT_CODE -eq 1 ]; then
        echo -e "  ${GREEN}PASS${RESET}"
    else
        echo -e "  ${RED}FAIL${RESET} (Exit code: $EXIT_CODE)"
    fi

    # Check for memory leaks
    if grep -q "All heap blocks were freed -- no leaks are possible" valgrind.log; then
        echo -e "  ${GREEN}No leaks detected${RESET}"
    else
        echo -e "  ${RED}Memory leaks detected!${RESET}"
        grep -E "lost|still" valgrind.log | sed 's/^/    /'
    fi
    echo ""
done