#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include "WISheader.h";
using namespace std;

const int INDEX_WIDTH = 15;
const int JOB_DETAILS_WIDTH = 10;

bool isValidWISParameters(int start, int finish, int profit);
bool compareByFinishTime(const WIS& firstJob, const WIS& secondJob);
void printWISContainer(const vector<WIS> container);
void printFormattedInputIntervals(const vector<WIS> container);
int findLastNonConflictingJob(const vector<WIS>& jobs, int index);
void purgeInputErrors(string errorMessage);

int main() {
	// You are given a list of jobs to complete and you only have one machine.
	// Each job has start time(S), finish time(F) and a weight(W).Some sets of intervals overlap and some sets do not.
	// The goal is to find the maximum profit subset of mutually compatible jobs*. In this problem, we must focus on maximum profit.
	// * Compatible jobs are jobs that don’t overlap.

	cout << "++++ Weighted Interval Sceduling with Bottom up dynamic programming ++++\n";

	int intervals;
	cout << "Enter number of Intervals: ";

	// Handle input errors
	while (!(cin >> intervals) || intervals <= 0) {
		purgeInputErrors("\nError: Invalid Input\nPlease enter a positive integer for the number of intervals: ");
	}

	// Create a container to store WIS 
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
		else if (isValidWISParameters(start, finish, profit)) {
			// Then check for valid WIS record
			jobs.emplace_back(start, finish, profit);
		}
	}

	if (invalidEntryDetected) {
		cout << "\nPlease note that one or more entries were invalid and excluded from the data set\n";
	}

	// Sort by finish times
	sort(jobs.begin(), jobs.end(), compareByFinishTime);

	// Display the results
	cout << "\nSorted Input Intervals By Finishing Time:\n";
	printFormattedInputIntervals(jobs);

	/* First Attempt */

	// Initialize DP arrays
	vector<int> dp(jobs.size());
	vector<int> p(jobs.size()); // Stores the index of the previous non-conflicting job

	// Base case
	dp[0] = jobs[0].getProfit();
	p[0] = -1; // No previous job for the first job

	// Bottom-up calculation of DP values
	for (int i = 1; i < jobs.size(); ++i) {
		int inclProfit = jobs[i].getProfit();
		int l = findLastNonConflictingJob(jobs, i);
		if (l != -1) {
			inclProfit += dp[l];
		}
		dp[i] = max(dp[i - 1], inclProfit);
		p[i] = (dp[i] == inclProfit) ? l : p[i - 1];
	}

	// The maximum profit is in the last cell
	cout << "\nMaximum profit of non-overlapping scheduling is " << dp[jobs.size() - 1] << endl;

	// Reconstruct the solution
	vector<WIS> optimalSet;
	int i = jobs.size() - 1; // Start from the last job
	while (i >= 0) {
		// If the current job is part of the optimal solution
		if (i == 0 || dp[i] != dp[i - 1]) {
			optimalSet.push_back(jobs[i]);
			i = p[i]; // Jump to the previous job included in the optimal solution
		}
		else {
			i--; // Move to the previous job
		}
	}

	// Reverse the optimalSet vector as we collected it in reverse
	reverse(optimalSet.begin(), optimalSet.end());

	// Display the schedules that comprise the maximum profit
	cout << "The jobs involved in the maximum profit are: ";
	for (WIS job : optimalSet) {
		job.printFormattedInterval();
	}

	return 0;
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
		/*
		else {
			cout << "\nError: Invalid Interval\nStart Time Must Be Less Than Finish Time *Entry Discarded*\n";
		}
		*/
	}
	/*
	else {
		cout << "\nError: Start Time, Finish Time, AND Weight Must Be Values Greater Than 0 *Entry Discarded*\n";
	}
	*/

	return isValid;
}

// Sorting logic for the std::sort method
bool compareByFinishTime(const WIS& firstJob, const WIS& secondJob) {
	return firstJob.getFinishTime() < secondJob.getFinishTime();
}

void printWISContainer(vector<WIS> container) {
	if (!container.empty()) {
		cout << "\nNo WIS Records To Process\n";
	}
	
	for (WIS element : container) {
		element.printFormattedInterval();
	}
}

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

int findLastNonConflictingJob(const vector<WIS>& jobs, int index) {
	// Iterate backwards through container to find the last non-conflicting job at the given index;
	for (int i = index - 1; i > 0; --i) {
		// We already ensured that the start and finish times are valid, so now we just check the edges of the intervals
		if (jobs[i].getFinishTime() <= jobs[index].getStartTime()) {
			return i;
		}
	}
	return -1; // No non-conflicting job found
}

// Resets cin object to a useable state after an input error
void purgeInputErrors(string errorMessage) {
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << errorMessage;
}
