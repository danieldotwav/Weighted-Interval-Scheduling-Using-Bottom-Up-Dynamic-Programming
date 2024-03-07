# Weighted Interval Scheduling Program

## Introduction

This program implements the Weighted Interval Scheduling (WIS) algorithm using a bottom-up dynamic programming approach. It is designed to find the optimal set of non-overlapping jobs (intervals) that maximizes the total profit. Each job is defined by a start time, finish time, and profit (weight).

## Files Description

- **WISalgorithm.cpp**: Contains the main algorithm functions to determine the optimal set of jobs based on their start time, finish time, and profit. It includes functions for user input validation, input error handling, and job sorting based on finish time.

- **WISalgorithm.h**: Header file for the WISalgorithm.cpp, declaring the functions used in the algorithm.

- **WISheader.h**: Defines the WIS class, encapsulating the details of a job, including start time, finish time, profit, and functions for input validation and formatting.

- **WISmain.cpp**: The main driver of the program. It prompts the user for the number of jobs, collects job details, and uses the WIS algorithm to find and display the optimal job set and maximum profit. It also includes test cases demonstrating expected outcomes for various inputs.

## Usage

1. Compile the program using a suitable C++ compiler, ensuring all files are included.
2. Run the executable.
3. Follow the prompts to enter the number of jobs and their details (start time, finish time, and profit).
4. The program will then display the sorted list of jobs by their finishing time, the optimal set of non-overlapping jobs, and the maximum profit.

## Test Cases

The program includes a variety of test cases to verify its functionality, ranging from simple scenarios with a few intervals to more complex situations with overlapping jobs and varying profits.

### Case 1
- **Intervals**: 6
- **Input**:
  - 1 3 5
  - 2 5 6
  - 4 6 5
  - 6 7 4
  - 5 8 11
  - 7 9 2
- **Expected Optimal Job Set**: {(2, 5, 6), (5, 8, 11)}
- **Expected Maximum Profit**: 17

### Case 2
- **Intervals**: 4
- **Input**:
  - 1 2 50
  - 3 5 20
  - 6 19 100
  - 2 10 200
- **Expected Optimal Job Set**: {(1, 2, 50), (2, 10, 200)}
- **Expected Maximum Profit**: 250

### Case 3
- **Intervals**: 7
- **Input**:
  - 1 4 3
  - 3 5 2
  - 0 6 9
  - 4 7 7
  - 3 8 4
  - 5 9 4
  - 6 10 10
- **Expected Optimal Job Set**: {(1, 4, 3), (6, 10, 10)}
- **Expected Maximum Profit**: 13

### Case 4
- **Intervals**: 8
- **Input**:
  - 6 8 2
  - 5 7 1
  - 8 11 4
  - 3 5 1
  - 4 7 1
  - 0 3 5
  - 1 4 2
  - 7 9 3
- **Expected Optimal Job Set**: {(1, 4, 2), (6, 8, 2), (8, 11, 4)}
- **Expected Maximum Profit**: 8

### Case 5
- **Intervals**: 6
- **Input**:
  - 5 7 7
  - 7 8 2
  - 8 9 1
  - 9 11 2
  - 11 12 3
  - 4 8 2
- **Expected Optimal Job Set**: {(5, 7, 7), (7, 8, 2), (8, 9, 1), (9, 11, 2), (11, 12, 3)}
- **Expected Maximum Profit**: 15

### Case 6
- **Intervals**: 7
- **Input** (Note: Contains invalid input 'x 9 1' which is skipped):
  - 4 7 4
  - 7 4 2
  - x 9 1
  - 9 11 2
  - 1 3 3
  - 8 1 9
  - 2 4 6
- **Expected Optimal Job Set**: {(2, 4, 6), (4, 7, 4), (9, 11, 2)}
- **Expected Maximum Profit**: 12

### Case 7
- **Intervals**: 1
- **Input**:
  - 0 0 0
- **Expected Optimal Job Set**: {}
- **Expected Maximum Profit**: 0

### Case 8
- **Intervals**: 3
- **Input**:
  - 1 2 3
  - 1 2 3
  - 1 2 3
- **Expected Optimal Job Set**: {(1, 2, 3)}
- **Expected Maximum Profit**: 3

### Case 9
- **Intervals**: 3
- **Input**:
  - 1 2 4
  - 1 2 8
  - 1 2 4
- **Expected Optimal Job Set**: {(1, 2, 8)}
- **Expected Maximum Profit**: 8

### Case 10
- **Intervals**: 5
- **Input**:
  - 4 7 9
  - 0 4 7
  - 1 4 6
  - 6 6 4
  - 7 10 5
- **Expected Optimal Job Set**: {(0, 4, 7), (4, 7, 9)}
- **Expected Maximum Profit**: 16

### Additional Notes for Cases

- For **Case 6**, note the presence of an invalid input (`x 9 1`). This entry is skipped, demonstrating the program's ability to handle invalid data gracefully.
- **Case 7** tests the algorithm with no intervals, showing its capability to handle edge cases.
- **Cases 8 to 10** further test the algorithm's robustness with varying numbers of intervals and profits.

## Algorithm Logic for Determining the Optimal Set of Non-Overlapping Schedules

The algorithm follows a dynamic programming approach, initially sorting jobs by finish time. It initializes a profit table, iteratively computes the maximum profit for including or excluding each job based on the last non-conflicting job, and updates a list of selected jobs accordingly. The process identifies the optimal set of non-overlapping jobs and the maximum profit by considering each job's contribution to the total profit in a bottom-up manner. This ensures an optimal selection of jobs with the maximum possible profit.




