#include <iostream>
#include "WISheader.h";
using namespace std;

bool isValidWISParameters(int start, int finish, int profit);
void sortWISContainer(WIS* container, int intervals);
void printWISContainer(WIS* container, int intervals);

int main() {
	// You are given a list of jobs to complete and you only have one machine.
	// Each job has start time(S), finish time(F) and a weight(W).Some sets of intervals overlap and some sets do not.
	// The goal is to find the maximum profit subset of mutually compatible jobs*. In this problem, we must focus on maximum profit.
	// * Compatible jobs are jobs that don’t overlap.

	cout << "++++ Weighted Interval Sceduling with Bottom up dynamic programming ++++\n";

	int intervals;
	cout << "Enter number of Intervals: ";
	cin >> intervals;

	// Create a container to store user intervals
	WIS* jobs = new WIS[intervals];

	// Populate WIS objects "intervals" number of times
	cout << "Enter Start time, Finish time, and Weight separated by a space:\nSi Fi Wi\n";

	int tempStart, tempFinish, tempProfit, numIntervalsProcessed = 0;
	for (int i = 0; i < intervals; ++i) {
		cin >> tempStart >> tempFinish >> tempProfit;
		
		// Only populate array with valid data
		if (isValidWISParameters(tempStart, tempFinish, tempProfit)) {
			jobs[i].setStartTime(tempStart);
			jobs[i].setFinishTime(tempFinish);
			jobs[i].setProfit(tempProfit);
			++numIntervalsProcessed;
		}
		else {
			--i;
		}
	}

	// Sort based on finish times
	sortWISContainer(jobs, numIntervalsProcessed);
	printWISContainer(jobs, numIntervalsProcessed);

	// Free up dynamically allocated memory
	delete[] jobs;

	return 0;
}

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

void sortWISContainer(WIS* container, int intervals) {
	for (int i = 0; i < intervals - 1; ++i) {
		for (int j = 0; j < intervals - i - 1; ++j) {
			if (container[j].getFinishTime() > container[j + 1].getFinishTime()) {
				// Swap the elements
				WIS temp = container[j];
				container[j] = container[j + 1];
				container[j + 1] = temp;
			}
		}
	}
}

void printWISContainer(WIS* container, int intervals) {
	for (int i = 0; i < intervals; ++i) {
		container[i].printFormattedInterval();
	}
}
