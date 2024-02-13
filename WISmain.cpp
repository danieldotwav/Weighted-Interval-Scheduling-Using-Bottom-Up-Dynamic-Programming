#include <iostream>
#include "WISheader.h";
using namespace std;

int main() {
	// You are given a list of jobs to complete and you only have one machine.
	// Each job has start time(S), finish time(F) and a weight(W).Some sets of intervals overlap and some sets do not.
	// The goal is to find the maximum profit subset of mutually compatible jobs*. In this problem, we must focus on maximum profit.
	// * Compatible jobs are jobs that don’t overlap.

	int intervals;
	cout << "Enter number of Intervals: ";
	cin >> intervals;

	cout << "Enter Start time, Finish time, and Weight separated by a space:\n Si Fi Wi\n";

	// Populate WIS objects "intervals" number of times
	for (int i = 0; i < intervals; ++i) {

	}
	

	return 0;
}