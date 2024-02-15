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
void printFormattedInputIntervals(const vector<WIS> container);

vector<WIS> getOptimalSet(const vector<WIS>& jobs);
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
	cout << "The jobs involved in the maximum profit are: ";
	for (WIS job : optimalSet) {
		job.printFormattedInterval();
	}

	cout << "\n\nTerminating program...\n";
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

vector<WIS> getOptimalSet(const vector<WIS>& jobs) {
	int numJobs = jobs.size();

	// Create a table to store solutions of subproblems
	vector<int> maxProfitUpToJob(numJobs + 1, 0); // Use a 1-based index for the job list
	vector<int> solution(numJobs + 1, -1); // Keep track of chosen jobs

	// Initialize the table to 0 as a base condition
	maxProfitUpToJob[0] = 0;

	// Fill the table using a bottom-up approach
	for (int j = 1; j <= numJobs; ++j) {
		// Find the last job that does not conflict with the current job
		int lastNonConflicting = findLastNonConflictingJob(jobs, j - 1);
		int includeProfit = jobs[j - 1].getProfit() +
			(lastNonConflicting == -1 ? 0 : maxProfitUpToJob[lastNonConflicting + 1]);

		// Check if the current job yields a better profit than not including it
		if (includeProfit > maxProfitUpToJob[j - 1]) {
			maxProfitUpToJob[j] = includeProfit;
			solution[j] = lastNonConflicting + 1; // Store the index of the last non-conflicting job
		}
		else {
			maxProfitUpToJob[j] = maxProfitUpToJob[j - 1];
			solution[j] = solution[j - 1];
		}
	}

	// Print the maximum profit to the user
	cout << "\nMaximum profit of non-overlapping scheduling is " << maxProfitUpToJob[numJobs] << endl;

	vector<WIS> optimalSolutionSet;
	int currentIndex = numJobs;
	cout << "Reconstructing the optimal set:" << endl;
	while (currentIndex > 0) {
		cout << "Current index: " << currentIndex << " | Solution at current index: " << solution[currentIndex] << endl;
		if (solution[currentIndex] != solution[currentIndex - 1]) {
			cout << "Adding job " << currentIndex - 1 << " to the optimal set." << endl;
			optimalSolutionSet.push_back(jobs[currentIndex - 1]);
			currentIndex = solution[currentIndex]; // Consider checking this assignment
		}
		else {
			--currentIndex;
		}
	}

	// The solution is constructed in reverse, so we need to reverse it
	reverse(optimalSolutionSet.begin(), optimalSolutionSet.end());

	return optimalSolutionSet;
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

// Resets cin object to a useable state after an input error
void purgeInputErrors(string errorMessage) {
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << errorMessage;
}
