#include <iostream>
#include "WISheader.h";
using namespace std;

bool isValidWISParameters(int start, int finish, int weight);

int main() {
	// You are given a list of jobs to complete and you only have one machine.
	// Each job has start time(S), finish time(F) and a weight(W).Some sets of intervals overlap and some sets do not.
	// The goal is to find the maximum profit subset of mutually compatible jobs*. In this problem, we must focus on maximum profit.
	// * Compatible jobs are jobs that don’t overlap.

	int intervals;
	cout << "Enter number of Intervals: ";
	cin >> intervals;

	// Create a container to store user intervals
	WIS* jobs = new WIS[intervals];

	// Populate WIS objects "intervals" number of times
	cout << "Enter Start time, Finish time, and Weight separated by a space:\nSi Fi Wi\n";

	int tempStart, tempFinish, tempWeight;
	for (int i = 0; i < intervals; ++i) {
		cin >> tempStart >> tempFinish >> tempWeight;
		
		// Only populate array with valid data
		if (isValidWISParameters(tempStart, tempFinish, tempWeight)) {
			jobs[i].setStartTime(tempStart);
			jobs[i].setFinishTime(tempFinish);
			jobs[i].setWeight(tempWeight);
		}
	}

	// Sort based on finish times
	

	// Free up dynamically allocated memory

	return 0;
}

bool isValidWISParameters(int start, int finish, int weight) {
	bool isValid = false;
	// First check for negative numbers
	if (start > 0 && finish > 0 && weight > 0) {
		// Then check for compatible time window
		if (start < finish) {
			isValid = true;
		}
	}

	return isValid;
}