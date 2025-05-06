#!/bin/bash

# Color constants
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
BLUE='\033[0;34m'
MAGENTA='\033[0;35m'
CYAN='\033[0;36m'
WHITE='\033[0;37m'
NC='\033[0m' # No Color
RESET='\033[0m' # Reset color

# Function to print in red
print_red() {
    echo -e "${RED}$1${RESET}"
}

# Function to print in green
print_green() {
    echo -e "${GREEN}$1${RESET}"
}

# Function to print in yellow
print_yellow() {
    echo -e "${YELLOW}$1${RESET}"
}

# Function to print in blue
print_blue() {
    echo -e "${BLUE}$1${RESET}"
}

# Function to print in magenta
print_magenta() {
    echo -e "${MAGENTA}$1${RESET}"
}

# Function to print in cyan
print_cyan() {
    echo -e "${CYAN}$1${RESET}"
}

# Function to print in white
print_white() {
    echo -e "${WHITE}$1${RESET}"
}