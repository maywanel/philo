# philo

## Table of Contents
- [Project Overview](#project-overview)
- [Directory Structure](#directory-structure)
- [How It Works](#how-it-works)
- [Building and Running](#building-and-running)
- [Testing](#testing)
- [Bonus Version](#bonus-version)
- [License](#license)

---

## Project Overview

**philo** is an implementation of the classic Dining Philosophers problem, a standard exercise in concurrent and parallel programming. The project simulates philosophers who alternately think, eat, and try to avoid deadlock while sharing limited resources (forks). This repository contains both the standard and a "bonus" version of the solution, along with a comprehensive test suite.

---

## Directory Structure

```
philo/
│
├── philo/               # Main implementation
│   ├── Makefile
│   ├── philo.c
│   ├── philo.h
│   └── src/
│       └── ...          # Additional source files
│
├── philo_bonus/         # Bonus (multi-process) implementation
│   ├── Makefile
│   ├── philo_bonus.c
│   ├── philo_bonus.h
│   └── src/
│       └── ...          # Additional source files
│
├── philo-tester/        # Automated test scripts and utilities
│   ├── README.md
│   ├── philosopher_tester.sh
│   ├── test_cases/
│   └── utils/
```

---

## How It Works

### The Problem

The Dining Philosophers problem involves a number of philosophers sitting around a table. Each philosopher alternates between thinking and eating. To eat, a philosopher needs two forks, but there are only as many forks as philosophers, and each fork is shared between neighbors. The challenge is to design a system where philosophers can eat without causing a deadlock or starvation.

### My Implementation

- **philo/**: Contains the C implementation using threads and mutexes to synchronize philosophers’ actions, and avoid deadlock.
- **philo_bonus/**: Contains an enhanced version, using processes and semaphores, to further challenge process synchronization.
- Each philosopher is represented by a thread (or process in the bonus), which simulates the cycle of thinking, picking up forks, eating, and sleeping.
- Careful attention is paid to avoid deadlock and data race, ensuring every philosopher gets a chance to eat.

---

## Building and Running

### Prerequisites

- GCC or any C compiler
- Make utility
- Unix-like environment (Linux, macOS)

### Build

**Standard version:**
```bash
cd philo
make
```

**Bonus version:**
```bash
cd ../philo_bonus
make
```

### Run

**Standard version:**
```bash
./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [optional_number_of_times_each_philosopher_must_eat]
```

**Example:**
```bash
./philo 5 800 200 200
```

**Bonus version:**  
(similar usage, but supports process-based concurrency)
```bash
./philo_bonus 5 800 200 200
```

---

## Testing

The project includes an automated tester in the `philo-tester` directory:

- **philo-tester/philosopher_tester.sh**: Run this script to validate your implementation with various test cases.
- **philo-tester/test_cases/**: Contains input scenarios.
- **philo-tester/utils/**: Utilities for testing or analysis.

**To run the tests:**
```bash
cd philo-tester
bash philosopher_tester.sh
```
Note : philo-tester need more work to cover all the importance tests if u have a something to add feel free to open issue or contact me
---

## Bonus Version

The `philo_bonus` directory implements the solution using processes and semaphores, suitable for advanced concurrency challenges. Build and run it similarly to the standard version.

---

## License

This project is provided for educational purposes and does not include a specific license by default. If you wish to use or modify this code, please add a license file.

---

## Credits

Developed by maywanel as part of a concurrency programming project.

---

For any questions, feel free to open an issue or contact me.
