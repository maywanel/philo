# filepath: /philo-tester/philo-tester/utils/helpers.sh

#!/bin/bash

# Utility functions for the 42 philosophers project testing

# Function to log messages with a timestamp
log_message() {
    local message="$1"
    echo "$(date '+%Y-%m-%d %H:%M:%S') - $message"
}

# Function to check the exit status of a command
check_exit_status() {
    local status=$1
    if [ $status -ne 0 ]; then
        log_message "Error: Command failed with exit status $status"
        return 1
    fi
    return 0
}

# Function to format test results
format_result() {
    local test_name="$1"
    local result="$2"
    if [ "$result" == "success" ]; then
        print_green "[Test Passed] - $test_name"
    else
        print_red "[Test Failed] - $test_name"
    fi
}

# Function to pause execution and wait for user input
pause_execution() {
    read -p "Press [Enter] to continue..."
}

# Function to check if a process is running
is_process_running() {
    local pid=$1
    if ps -p $pid > /dev/null; then
        return 0
    else
        return 1
    fi
}

# Function to kill all philosopher processes
kill_all_philosophers() {
    killall -9 philo philo_bonus 2>/dev/null
    return 0
}

# Function to measure execution time
measure_time() {
    local start_time=$(date +%s.%N)
    "$@"
    local end_time=$(date +%s.%N)
    local elapsed=$(echo "$end_time - $start_time" | bc)
    echo "$elapsed seconds"
}