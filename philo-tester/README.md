# philo-tester Testing Project

This repository contains a suite of tests for the 42 philosophers project, designed to ensure the correctness and robustness of the implementation. The tests cover various scenarios, including basic functionality, edge cases, and error handling.

## Project Structure

- **philosopher_tester.sh**: The main script that orchestrates the testing process by calling various test cases.
- **test_cases/**: Directory containing individual test scripts:
  - **basic_tests.sh**: Tests fundamental functionalities of the philosophers project.
  - **death_tests.sh**: Simulates scenarios where philosophers may "die" due to synchronization issues.
  - **edge_cases.sh**: Explores edge cases and extreme situations.
  - **error_handling.sh**: Verifies the project's response to erroneous inputs.
- **utils/**: Directory containing utility scripts:
  - **colors.sh**: Defines color constants and functions for colored terminal output.
  - **helpers.sh**: Contains utility functions for logging and result formatting.
  - **validation.sh**: Functions for validating inputs and outputs of the philosophers project.

## Running the Tests

To run the tests, execute the main script:

```bash
bash philosopher_tester.sh
```

Ensure that all test scripts are executable. You can make them executable with the following command:

```bash
chmod +x test_cases/*.sh utils/*.sh
```

## Contribution

Feel free to contribute by adding new test cases or improving existing ones. Ensure that all tests are well-documented and follow the project's coding standards.