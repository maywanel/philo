#!/bin/bash

# Source the utility files
source utils/colors.sh
source utils/helpers.sh
source utils/validation.sh

# Path to the philosopher executable (supports both mandatory and bonus parts)
PHILO_PATH="../philo/philo"
PHILO_BONUS_PATH="../philo_bonus/philo_bonus"

# Function to run a basic test
run_basic_test() {
    local test_name=$1
    local nbr_philos=$2
    local time_die=$3
    local time_eat=$4
    local time_sleep=$5
    local nbr_meals=$6
    local expected_result=$7
    local executable=${8:-$PHILO_PATH}
    
    echo -e "${YELLOW}Running: ${test_name}${RESET}"
    echo -e "${CYAN}Command: $executable $nbr_philos $time_die $time_eat $time_sleep $nbr_meals${RESET}"
    
    # Run with timeout to prevent hanging tests
    if [ -z "$nbr_meals" ]; then
        timeout 10s $executable $nbr_philos $time_die $time_eat $time_sleep > test_output.txt 2>&1 &
    else
        timeout 10s $executable $nbr_philos $time_die $time_eat $time_sleep $nbr_meals > test_output.txt 2>&1 &
    fi
    
    PID=$!
    
    # Wait for process to finish or be killed by timeout
    wait $PID
    EXIT_CODE=$?
    
    # Check the result
    if [ "$EXIT_CODE" -eq 124 ]; then
        # Timed out - likely running indefinitely as expected
        if [ "$expected_result" == "should_run" ]; then
            echo -e "${GREEN}✓ Test passed: Program ran without deaths as expected${RESET}"
            killall -9 $(basename $executable) 2>/dev/null
            return 0
        else
            echo -e "${RED}✗ Test failed: Program ran too long${RESET}"
            return 1
        fi
    elif [ "$EXIT_CODE" -eq 0 ]; then
        # Program terminated normally
        if [ "$expected_result" == "should_terminate" ]; then
            echo -e "${GREEN}✓ Test passed: Program terminated normally${RESET}"
            return 0
        else
            echo -e "${RED}✗ Test failed: Program terminated but should have kept running${RESET}"
            return 1
        fi
    else
        # Program crashed or had an error
        echo -e "${RED}✗ Test failed: Program exited abnormally with code $EXIT_CODE${RESET}"
        return 1
    fi
}

# Basic test scenarios
echo -e "${BLUE}========== BASIC TESTS ==========${RESET}"

# Test 1: 5 philosophers should run indefinitely with enough time
run_basic_test "5 philosophers with enough time" 5 800 200 200 "" "should_run"

# Test 2: 4 philosophers eating 3 times each, should terminate
run_basic_test "4 philosophers eating 3 times each" 4 410 200 200 3 "should_terminate"

# Test 3: 1 philosopher should die (can't eat with only 1 fork)
run_basic_test "1 philosopher should die" 1 800 200 200 "" "should_terminate"

# Test 4: Philosophers with barely enough time (edge case)
run_basic_test "Philosophers with barely enough time" 5 310 100 100 "" "should_run"

# Test 5: 20 philosophers stress test
run_basic_test "20 philosophers stress test" 20 800 200 200 "" "should_run"

# Check bonus part if it exists
if [ -f "$PHILO_BONUS_PATH" ]; then
    echo -e "\n${BLUE}========== BONUS TESTS ==========${RESET}"
    
    # Run the same tests with the bonus part
    run_basic_test "BONUS: 5 philosophers with enough time" 5 800 200 200 "" "should_run" "$PHILO_BONUS_PATH"
    run_basic_test "BONUS: 4 philosophers eating 3 times each" 4 410 200 200 3 "should_terminate" "$PHILO_BONUS_PATH"
    run_basic_test "BONUS: 1 philosopher should die" 1 800 200 200 "" "should_terminate" "$PHILO_BONUS_PATH"
fi

echo -e "${BLUE}========== BASIC TESTS COMPLETED ==========${RESET}"

# Clean up
rm -f test_output.txt
killall -9 philo philo_bonus 2>/dev/null