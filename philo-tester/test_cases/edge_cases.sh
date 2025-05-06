#!/bin/bash

# Source the utility files
source utils/colors.sh
source utils/helpers.sh
source utils/validation.sh

# Path to the philosopher executable (supports both mandatory and bonus parts)
PHILO_PATH="../philo/philo"
PHILO_BONUS_PATH="../philo_bonus/philo_bonus"

# Function to run an edge case test
run_edge_test() {
    local test_name=$1
    local nbr_philos=$2
    local time_die=$3
    local time_eat=$4
    local time_sleep=$5
    local expected_result=$6
    local executable=${7:-$PHILO_PATH}
    
    echo -e "${YELLOW}Running: ${test_name}${RESET}"
    echo -e "${CYAN}Command: $executable $nbr_philos $time_die $time_eat $time_sleep${RESET}"
    
    # Run the program and capture exit code
    $executable $nbr_philos $time_die $time_eat $time_sleep > test_output.txt 2>&1
    EXIT_CODE=$?
    
    # Check the result based on expected behavior
    if [ "$expected_result" == "should_error" ]; then
        if [ $EXIT_CODE -ne 0 ]; then
            echo -e "${GREEN}✓ Test passed: Program correctly handled invalid input${RESET}"
            return 0
        else
            echo -e "${RED}✗ Test failed: Program did not reject invalid input${RESET}"
            return 1
        fi
    else
        if [ $EXIT_CODE -eq 0 ]; then
            echo -e "${GREEN}✓ Test passed: Program handled edge case${RESET}"
            return 0
        else
            echo -e "${RED}✗ Test failed: Program crashed with edge case${RESET}"
            return 1
        fi
    fi
}

# Edge test scenarios
echo -e "${BLUE}========== EDGE CASE TESTS ==========${RESET}"

# Test case 1: Zero philosophers (should reject)
run_edge_test "Zero philosophers" 0 800 200 200 "should_error"

# Test case 2: Negative philosopher count (should reject)
run_edge_test "Negative philosopher count" -5 800 200 200 "should_error"


# Test case 4: Extremely large number of philosophers
run_edge_test "Large number of philosophers" 201 800 200 200 "should_error"

# Test case 5: Extremely short times
run_edge_test "Extremely short times" 5 60 60 60 "should_handle"

# Test case 6: High time values
run_edge_test "High time values" 5 9999 9999 9999 "should_handle"

# Test case 7: Negative time values (should reject)
run_edge_test "Negative time values" 5 -800 -200 -200 "should_error"

# Check bonus part if it exists
if [ -f "$PHILO_BONUS_PATH" ]; then
    echo -e "\n${BLUE}========== BONUS EDGE CASE TESTS ==========${RESET}"
    
    # Run the same edge tests with the bonus part
    run_edge_test "BONUS: Zero philosophers" 0 800 200 200 "should_error" "$PHILO_BONUS_PATH"
    run_edge_test "BONUS: Negative philosopher count" -5 800 200 200 "should_error" "$PHILO_BONUS_PATH"
    run_edge_test "BONUS: Large number of philosophers" 201 800 200 200 "should_error" "$PHILO_BONUS_PATH"
    run_edge_test "BONUS: Extremely short times" 5 60 60 60 "should_handle" "$PHILO_BONUS_PATH"
    run_edge_test "BONUS: High time values" 5 9999 9999 9999 "should_handle" "$PHILO_BONUS_PATH"
    run_edge_test "BONUS: Negative time values" 5 -800 -200 -200 "should_error" "$PHILO_BONUS_PATH"
fi

echo -e "${BLUE}========== EDGE CASE TESTS COMPLETED ==========${RESET}"

# Clean up
rm -f test_output.txt
killall -9 philo philo_bonus 2>/dev/null