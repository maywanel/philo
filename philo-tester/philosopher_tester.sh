#!/bin/bash

# This script orchestrates the testing process for the 42 philosophers project.

# Load utility functions
source ./utils/colors.sh
source ./utils/helpers.sh
source ./utils/validation.sh

# Display menu and get user choice
show_menu() {
    echo -e "${BLUE}======== Philosophers Tester ========${RESET}"
    echo -e "1. ${CYAN}Run Basic Tests${RESET}"
    echo -e "2. ${CYAN}Run Death Tests${RESET}"
    echo -e "3. ${CYAN}Run Edge Cases${RESET}"
    echo -e "4. ${CYAN}Run Error Handling Tests${RESET}"
    echo -e "5. ${CYAN}Run All Tests${RESET}"
    echo -e "0. ${CYAN}Exit${RESET}"
    echo -e "${BLUE}====================================${RESET}"
    echo -e "Enter your choice: "
    read choice
}

# Function to run selected test
run_selected_test() {
    case $1 in
        1)
            echo -e "${GREEN}Running Basic Tests...${RESET}"
            ./test_cases/basic_tests.sh
            ;;
        2)
            echo -e "${GREEN}Running Death Tests...${RESET}"
            ./test_cases/death_tests.sh
            ;;
        3)
            echo -e "${GREEN}Running Edge Cases...${RESET}"
            ./test_cases/edge_cases.sh
            ;;
        4)
            echo -e "${GREEN}Running Error Handling Tests...${RESET}"
            ./test_cases/error_handling.sh
            ;;
        5)
            run_all_tests
            ;;
        0)
            echo -e "${YELLOW}Exiting tester...${RESET}"
            exit 0
            ;;
        *)
            echo -e "${RED}Invalid choice. Please try again.${RESET}"
            ;;
    esac
}

# Function to run all test cases
run_all_tests() {
    echo -e "${GREEN}Running All Tests...${RESET}"
    
    echo -e "${GREEN}Running Basic Tests...${RESET}"
    ./test_cases/basic_tests.sh

    echo -e "${GREEN}Running Death Tests...${RESET}"
    ./test_cases/death_tests.sh

    echo -e "${GREEN}Running Edge Cases...${RESET}"
    ./test_cases/edge_cases.sh

    echo -e "${GREEN}Running Error Handling Tests...${RESET}"
    ./test_cases/error_handling.sh

    echo -e "${GREEN}All tests completed.${RESET}"
}

# Main execution
while true; do
    show_menu
    run_selected_test $choice
    echo ""
    echo -e "${YELLOW}Press Enter to continue...${RESET}"
    read
    clear
done