// This program implements the Weighted Interval Scheduling algorithm using a 
// bottom - up dynamic programming approach.The program is designed to find the 
// optimal set of non - overlapping jobs(intervals) that maximizes the total profit, 
// where each job has a start time, finish time, and profit(weight).


#include "WISheader.h"; // Contains WIS class definition/implementation
#include "WISalgorithm.h"; // Contains the 
#include <algorithm>
using namespace std;


int main() {
	cout << "++++ Weighted Interval Sceduling with Bottom up dynamic programming ++++\n";

	int intervals;
	cout << "Enter number of Intervals: ";

	// Handle input errors
	while (!(cin >> intervals) || intervals <= 0) {
		purgeInputErrors("\nError: Invalid Input\nPlease enter a positive integer for the number of intervals: ");
	}

	// Create a container to store the jobs
	vector<WIS> jobs;

	// Populate WIS container
	cout << "\nEnter Start time, Finish time, and Weight separated by a space:\nSi Fi Wi\n";

	int start, finish, profit;
	bool invalidEntryDetected = false;
	for (int i = 0; i < intervals; ++i) {
		// First check for valid input type
		if (!(cin >> start) || !(cin >> finish) || !(cin >> profit)) {
			purgeInputErrors("");
			invalidEntryDetected = true;
		}
		else {
			// Then check for valid WIS record
			if (isValidWISParameters(start, finish, profit)) {
				jobs.emplace_back(start, finish, profit);
			}
			else {
				invalidEntryDetected = true;
			}
		}
	}

	if (invalidEntryDetected) {
		cout << "\n*Please note that one or more entries were invalid and excluded from the data set\n";
	}

	// Sort by finish time
	sort(jobs.begin(), jobs.end(), compareByFinishTime);

	// Display the results
	cout << "\nSorted Input Intervals By Finishing Time:\n";
	printFormattedInputIntervals(jobs);

	/* MAIN ALGORITHM */
	vector<WIS> optimalSet = getOptimalSet(jobs);

	// Display the schedules that comprise the maximum profit
	cout << "\nThe jobs involved in the maximum profit are: ";
	for (WIS job : optimalSet) {
		job.printFormattedInterval();
	}

	cout << "\nTerminating program...\n";
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
*/