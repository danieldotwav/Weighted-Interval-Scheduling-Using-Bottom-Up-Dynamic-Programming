#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include "WISheader.h";
using namespace std;

const int INDEX_WIDTH = 15;
const int JOB_DETAILS_WIDTH = 10;

// === Main Algorithm Functions ===
vector<WIS> getOptimalSet(const vector<WIS>& jobs);
int findLastNonConflictingJob(const vector<WIS>& jobs, int index);
bool isValidWISParameters(int start, int finish, int profit);
bool compareByFinishTime(const WIS& firstJob, const WIS& secondJob);

// === Utility Functions ===
void printFormattedInputIntervals(const vector<WIS> container);
void purgeInputErrors(string errorMessage);

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

// === Main Algorithm Functions ===

vector<WIS> getOptimalSet(const vector<WIS>& jobs) {
	int numJobs = jobs.size();

	// Create a table to store solutions of subproblems
	vector<int> maxProfitUpToJob(numJobs + 1, 0); // Use a 1-based index for the job list
	vector<vector<WIS>> jobList(numJobs + 1); // Keep track of selected jobs

	// Initialize the base condition
	maxProfitUpToJob[0] = 0; // No profit with 0 jobs

	// Fill the table using a bottom-up approach
	for (int j = 1; j <= numJobs; ++j) {
		// Find the last job that does not conflict with the current job
		int lastNonConflicting = findLastNonConflictingJob(jobs, j - 1);
		int includeProfit = jobs[j - 1].getProfit() +
			(lastNonConflicting == -1 ? 0 : maxProfitUpToJob[lastNonConflicting + 1]);

		// Check if including the current job yields a better profit than excluding it
		if (includeProfit > maxProfitUpToJob[j - 1]) {
			maxProfitUpToJob[j] = includeProfit;
			if (lastNonConflicting != -1) {
				jobList[j] = jobList[lastNonConflicting + 1]; // Include all previous non-conflicting jobs
			}
			jobList[j].push_back(jobs[j - 1]); // Include this job
		}
		else {
			maxProfitUpToJob[j] = maxProfitUpToJob[j - 1];
			jobList[j] = jobList[j - 1]; // Carry forward the previous job list
		}
	}

	// Calculate and display the maximum profit to the user
	vector<WIS> optimalSet = jobList[numJobs];
	int maxProfit = 0;
	for (WIS element : optimalSet) {
		maxProfit += element.getProfit();
	}

	cout << "\nMaximum profit of non-overlapping scheduling is " << maxProfit;

	// The last element in jobList now contains the set of jobs that contribute to the maximum profit
	return optimalSet;
}

int findLastNonConflictingJob(const vector<WIS>& jobs, int index) {
	// Iterate backwards through container to find the last non-conflicting job at the given index;
	for (int i = index; i >= 0; --i) {
		// We already ensured that the start and finish times are valid, so now we just check the edges of the intervals
		if (jobs[i].getFinishTime() <= jobs[index].getStartTime()) {
			return i;
		}
	}
	return -1; // No non-conflicting job found
}

// Validates record data and returns the state of the values as a boolean
bool isValidWISParameters(int start, int finish, int profit) {
	bool isValid = false;
	// First check for negative numbers
	if (start > 0 && finish > 0 && profit > 0) {
		// Then check for compatible time window
		if (start < finish) {
			isValid = true;
		}
	}

	return isValid;
}

// Sorting logic for the std::sort method
bool compareByFinishTime(const WIS& firstJob, const WIS& secondJob) {
	return firstJob.getFinishTime() < secondJob.getFinishTime();
}

// === Utility Functions ===

void printFormattedInputIntervals(const vector<WIS> container) {
	cout << "\t" << left << setw(INDEX_WIDTH) <<
		"Index<i>" << setw(JOB_DETAILS_WIDTH) <<
		"S<i>" << setw(JOB_DETAILS_WIDTH) <<
		"F<i>" << setw(JOB_DETAILS_WIDTH) <<
		"W<i>\n";

	int numWISRecords = container.size();
	for (int i = 0; i < numWISRecords; ++i) {
		cout << "\t" <<
			setw(INDEX_WIDTH) << i + 1 <<
			setw(JOB_DETAILS_WIDTH) << container[i].getStartTime() <<
			setw(JOB_DETAILS_WIDTH) << container[i].getFinishTime() <<
			setw(JOB_DETAILS_WIDTH) << container[i].getProfit() << endl;
	}
}

// Resets cin object to a useable state after an input error
void purgeInputErrors(string errorMessage) {
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << errorMessage;
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