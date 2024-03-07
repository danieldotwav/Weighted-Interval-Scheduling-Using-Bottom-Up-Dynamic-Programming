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

## Algorithm Logic for Determining the Optimal Set of Non-Overlapping Schedules

The algorithm follows a dynamic programming approach, initially sorting jobs by finish time. It initializes a profit table, iteratively computes the maximum profit for including or excluding each job based on the last non-conflicting job, and updates a list of selected jobs accordingly. The process identifies the optimal set of non-overlapping jobs and the maximum profit by considering each job's contribution to the total profit in a bottom-up manner. This ensures an optimal selection of jobs with the maximum possible profit.




