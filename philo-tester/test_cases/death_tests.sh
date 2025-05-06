#!/bin/bash

# Source the utility files
source utils/colors.sh
source utils/helpers.sh
source utils/validation.sh

# Path to the philosopher executable (supports both mandatory and bonus parts)
PHILO_PATH="../philo/philo"
PHILO_BONUS_PATH="../philo_bonus/philo_bonus"

# Function to run a death test scenario
run_death_test() {
    local test_name=$1
    local nbr_philos=$2
    local time_die=$3
    local time_eat=$4
    local time_sleep=$5
    local executable=${6:-$PHILO_PATH}
    
    echo -e "${YELLOW}Running: ${test_name}${RESET}"
    echo -e "${CYAN}Command: $executable $nbr_philos $time_die $time_eat $time_sleep${RESET}"
    
    # Start the philosopher process with a timeout
    timeout 15s $executable $nbr_philos $time_die $time_eat $time_sleep > test_output.txt 2>&1 &
    PID=$!
    
    # Wait for a short time to allow philosophers to start
    sleep 2
    
    # Check if process ended (philosopher died)
    if ! ps -p $PID > /dev/null; then
        echo -e "${GREEN}✓ Test passed: A philosopher died as expected${RESET}"
        return 0
    else
        # Wait up to 10 more seconds for death
        for i in {1..10}; do
            sleep 1
            if ! ps -p $PID > /dev/null; then
                echo -e "${GREEN}✓ Test passed: A philosopher died as expected${RESET}"
                return 0
            fi
        done
        
        # Kill process if it's still running
        kill $PID 2>/dev/null
        echo -e "${RED}✗ Test failed: No philosopher died within expected time${RESET}"
        return 1
    fi
}

# Death test scenarios
echo -e "${BLUE}========== DEATH TESTS ==========${RESET}"

# Test case 1: Single philosopher with short time to die (can't eat alone)
run_death_test "Single philosopher should die" 1 800 200 200

# Test case 2: Multiple philosophers with tight timing
run_death_test "Philosophers with no time to eat" 5 100 200 200

# Test case 3: Quick death timer
run_death_test "Quick death timer (60ms)" 4 60 200 200

# Test case 4: Extremely tight timing
run_death_test "Extremely tight timing" 3 100 99 99

# Check bonus part if it exists
if [ -f "$PHILO_BONUS_PATH" ]; then
    echo -e "\n${BLUE}========== BONUS DEATH TESTS ==========${RESET}"
    
    # Run the same death tests with the bonus part
    run_death_test "BONUS: Single philosopher should die" 1 800 200 200 "$PHILO_BONUS_PATH"
    run_death_test "BONUS: Philosophers with no time to eat" 5 100 200 200 "$PHILO_BONUS_PATH"
    run_death_test "BONUS: Quick death timer (60ms)" 4 60 200 200 "$PHILO_BONUS_PATH"
    run_death_test "BONUS: Extremely tight timing" 3 100 99 99 "$PHILO_BONUS_PATH"
fi

echo -e "${BLUE}========== DEATH TESTS COMPLETED ==========${RESET}"

# Clean up
rm -f test_output.txt
killall -9 philo philo_bonus 2>/dev/null