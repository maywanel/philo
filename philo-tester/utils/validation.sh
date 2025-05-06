#!/bin/bash

# filepath: /home/moel-mes/Desktop/philo/philo-tester/utils/validation.sh

# This script contains functions for validating inputs and outputs of the philosophers project.

# Function to validate the number of philosophers
validate_philosopher_count() {
    if ! [[ "$1" =~ ^[0-9]+$ ]] || [ "$1" -le 0 ]; then
        echo "Error: Invalid philosopher count. It must be a positive integer."
        return 1
    fi
    return 0
}

# Function to validate time values
validate_time_value() {
    if ! [[ "$1" =~ ^[0-9]+$ ]] || [ "$1" -lt 0 ]; then
        echo "Error: Invalid time value. It must be a non-negative integer."
        return 1
    fi
    return 0
}

# Function to validate input arguments
validate_inputs() {
    if [ "$#" -lt 4 ]; then
        echo "Error: Not enough arguments provided."
        return 1
    fi

    validate_philosopher_count "$1" || return 1
    validate_time_value "$2" || return 1
    validate_time_value "$3" || return 1
    validate_time_value "$4" || return 1
    
    # Optional 5th argument (number of times each philosopher must eat)
    if [ "$#" -ge 5 ]; then
        validate_time_value "$5" || return 1
    fi

    return 0
}

# Function to validate philosopher output line format
validate_output_line() {
    # Expected format: timestamp_in_ms philosopher_id action_message
    if ! [[ "$1" =~ ^[0-9]+[[:space:]][0-9]+[[:space:]].*$ ]]; then
        echo "Error: Invalid output line format. Expected format is 'timestamp philo_id action'."
        return 1
    fi
    return 0
}

# Function to check if a philosopher died in the output
check_death_in_output() {
    if grep -q "died" "$1"; then
        return 0  # Death found
    else
        return 1  # No death found
    fi
}

# Function to count how many times philosophers ate
count_meals_in_output() {
    local philo_id=$1
    local output_file=$2
    
    # Count occurrences of "is eating" for the specified philosopher
    grep "$philo_id is eating" "$output_file" | wc -l
}