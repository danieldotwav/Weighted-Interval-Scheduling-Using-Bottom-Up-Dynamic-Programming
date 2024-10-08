// Program Summary: This program implements the Weighted Interval Scheduling algorithm using a bottom-up dynamic programming approach. The program is designed to find the optimal set of non-overlapping jobs (intervals) that maximizes the total profit, where each job has a start time, finish time, and profit (weight).

#include "WISheader.h"; // Contains WIS class definition/implementation
#include "WISalgorithm.h"; // Contains implementation of the main algorithm and utility functions
using namespace std;


int main() {
	cout << "++++ Weighted Interval Sceduling with Bottom up dynamic programming ++++\n";

	// Get number of intervals to process from user
	int intervals = promptUserForNumIntervals();
	
	// Create and populate container to store jobs
	vector<WIS> jobs = generateWISVectorFromUserInput(intervals);

	// Display the results
	cout << "\nSorted Input Intervals By Finishing Time:\n";
	printFormattedInputIntervals(jobs);

	/* MAIN ALGORITHM */
	vector<WIS> optimalSet = getOptimalSet(jobs);

	// Display the schedules that comprise the maximum profit
	cout << "\nThe jobs involved in the maximum profit are: ";
	printOptimalSet(optimalSet);

	cout << "\n\nTerminating program...\n";
	return 0;
}

/* === Test Cases ===

Case 1:
6 Intervals
1 3 5
2 5 6
4 6 5
6 7 4
5 8 11
7 9 2

Expected Optimal Job Set: {(2, 5, 6) (5, 8, 11)}
Expected Maximum Profit: 17


Case 2:
4 Intervals
1 2 50
3 5 20
6 19 100
2 10 200

Expected Optimal Job Set: {(1, 2, 50) (2, 10, 200)}
Expected Maximum Profit: 250


Case 3:
7 Intervals
1 4 3
3 5 2
0 6 9
4 7 7
3 8 4
5 9 4
6 10 10

Expected Optimal Job Set: {(1, 4, 3) (6, 10, 10)}
Expected Maximum Profit: 13


Case 4:
8 Intervals
6 8 2
5 7 1
8 11 4
3 5 1
4 7 1
0 3 5
1 4 2
7 9 3

Expected Optimal Job Set: {(1, 4, 2) (6, 8, 2) (8, 11, 4)}
Expected Maximum Profit: 8


Case 5:
6 Intervals
5 7 7
7 8 2
8 9 1
9 11 2
11 12 3
4 8 2

Expected Optimal Job Set: {(5, 7, 7) (7, 8, 2) (8, 9, 1) (9, 11, 2) (11, 12, 3)}
Expected Maximum Profit: 15


Case 6:
7 Intervals
4 7 4
7 4 2
x 9 1
9 11 2
1 3 3
8 1 9
2 4 6

Expected Optimal Job Set: {(2, 4, 6) (4, 7, 4) (9, 11, 2)}
Expected Maximum Profit: 12


Case 7:
1 Intervals
0 0 0

Expected Optimal Job Set: {}
Expected Maximum Profit: 0


Case 8:
3 Intervals
1 2 3
1 2 3
1 2 3

Expected Optimal Job Set: {(1, 2, 3)}
Expected Maximum Profit: 3

Case 9:
3 Intervals
1 2 4
1 2 8
1 2 4


Case 10:
5 Intervals

4 7 9
0 4 7
1 4 6
6 6 4
7 10 5

*/