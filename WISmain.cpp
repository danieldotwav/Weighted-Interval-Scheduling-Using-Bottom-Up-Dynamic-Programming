#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include "WISheader.h";
using namespace std;

const int INDEX_WIDTH = 15;
const int JOB_DETAILS_WIDTH = 8;

bool isValidWISParameters(int start, int finish, int profit);
bool compareByFinishTime(const WIS& firstJob, const WIS& secondJob);
void printWISContainer(const vector<WIS> container);
void printFormattedInputIntervals(const vector<WIS> container);

int main() {
	// You are given a list of jobs to complete and you only have one machine.
	// Each job has start time(S), finish time(F) and a weight(W).Some sets of intervals overlap and some sets do not.
	// The goal is to find the maximum profit subset of mutually compatible jobs*. In this problem, we must focus on maximum profit.
	// * Compatible jobs are jobs that don’t overlap.

	cout << "++++ Weighted Interval Sceduling with Bottom up dynamic programming ++++\n";

	int intervals;
	cout << "Enter number of Intervals: ";
	cin >> intervals;

	// Create a container to store WIS 
	vector<WIS> jobs;

	// Populate WIS container
	cout << "Enter Start time, Finish time, and Weight separated by a space:\nSi Fi Wi\n";

	int start, finish, profit;
	for (int i = 0; i < intervals; ++i) {
		cin >> start >> finish >> profit;
		
		// Only process valid data
		if (isValidWISParameters(start, finish, profit)) {
			WIS record(start, finish, profit);
			jobs.push_back(record);
		}
	}

	// Sort based on finish times
	sort(jobs.begin(), jobs.end(), compareByFinishTime);

	// Display the results
	cout << "\nSorted Input Intervals By Finishing Time:\n";
	printFormattedInputIntervals(jobs);

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
		else {
			cout << "\nERROR: Invalid Interval. Start Time Must Be Less Than Finish Time\nInvalid Entry Has Been Discarded\n";
		}
	}
	else {
		cout << "\nERROR: Start Time, Finish Time, AND Weight Must Be Values Greater Than 0\nInvalid Entry Has Been Discarded\n";
	}

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
