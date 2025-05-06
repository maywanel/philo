#!/bin/bash

# Source the utility files
source utils/colors.sh
source utils/helpers.sh
source utils/validation.sh

# Path to the philosopher executable (supports both mandatory and bonus parts)
PHILO_PATH="../philo/philo"
PHILO_BONUS_PATH="../philo_bonus/philo_bonus"

# Function to test error handling
run_error_test() {
    local test_name=$1
    local args=$2
    local expected_output=$3
    local executable=${4:-$PHILO_PATH}
    
    echo -e "${YELLOW}Running: ${test_name}${RESET}"
    echo -e "${CYAN}Command: $executable $args${RESET}"
    
    # Run the program and capture output and exit code
    $executable $args > test_output.txt 2>&1
    EXIT_CODE=$?
    
    # Check if the output contains the expected error message
    if [ $EXIT_CODE -ne 0 ] && grep -q "$expected_output" test_output.txt; then
        echo -e "${GREEN}✓ Test passed: Program correctly detected the error${RESET}"
        return 0
    else
        echo -e "${RED}✗ Test failed: Program did not properly handle the error${RESET}"
        echo -e "${RED}Expected error message containing: '$expected_output'${RESET}"
        echo -e "${CYAN}Actual output:${RESET}"
        cat test_output.txt
        return 1
    fi
}

# Error handling test scenarios
echo -e "${BLUE}========== ERROR HANDLING TESTS ==========${RESET}"

# Test case 1: No arguments
run_error_test "No arguments provided" "" "usage"

# Test case 2: Too few arguments
run_error_test "Too few arguments" "5 800" "usage"

# Test case 3: Non-numeric arguments
run_error_test "Non-numeric arguments" "five 800 200 200" "numeric"

# Test case 4: Negative values
run_error_test "Negative values" "5 -800 200 200" "positive"

# Test case 5: Zero philosophers
run_error_test "Zero philosophers" "0 800 200 200" "at least"

# Test case 6: Too many philosophers
run_error_test "Too many philosophers" "1000 800 200 200" "maximum"

# Test case 7: Invalid characters
run_error_test "Invalid characters in arguments" "5 800a 200 200" "numeric"

# Check bonus part if it exists
if [ -f "$PHILO_BONUS_PATH" ]; then
    echo -e "\n${BLUE}========== BONUS ERROR HANDLING TESTS ==========${RESET}"
    
    # Run the same error tests with the bonus part
    run_error_test "BONUS: No arguments provided" "" "usage" "$PHILO_BONUS_PATH"
    run_error_test "BONUS: Too few arguments" "5 800" "usage" "$PHILO_BONUS_PATH"
    run_error_test "BONUS: Non-numeric arguments" "five 800 200 200" "numeric" "$PHILO_BONUS_PATH"
    run_error_test "BONUS: Negative values" "5 -800 200 200" "positive" "$PHILO_BONUS_PATH"
fi

echo -e "${BLUE}========== ERROR HANDLING TESTS COMPLETED ==========${RESET}"

# Clean up
rm -f test_output.txt