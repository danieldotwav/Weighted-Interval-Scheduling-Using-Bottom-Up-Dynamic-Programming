#include "WISheader.h";
#include "WISalgorithm.h";
#include <algorithm>
#include <iomanip>

const int INDEX_WIDTH = 15;
const int JOB_DETAILS_WIDTH = 10;

// === Main Algorithm Functions ===

// Takes in a vector of WIS objects and returns a vector of non-conflicting jobs with the greatest profit
std::vector<WIS> getOptimalSet(const std::vector<WIS>& jobs) {
	int numJobs = jobs.size();

	// Create a table to store solutions of subproblems
	std::vector<int> maxProfitUpToJob(numJobs + 1, 0); // Use a 1-based index for the job list
	std::vector<std::vector<WIS>> jobList(numJobs + 1); // Keep track of selected jobs

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
	std::vector<WIS> optimalSet = jobList[numJobs];
	int maxProfit = 0;
	for (WIS element : optimalSet) {
		maxProfit += element.getProfit();
	}

	std::cout << "\nMaximum profit of non-overlapping scheduling is " << maxProfit << std::endl;

	// The last element in jobList now contains the set of jobs that contribute to the maximum profit
	return optimalSet;
}

int findLastNonConflictingJob(const std::vector<WIS>& jobs, int index) {
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

int promptUserForNumIntervals() {
	int intervals;
	std::cout << "Enter number of Intervals: ";

	// Handle input errors
	while (!(std::cin >> intervals) || intervals <= 0) {
		purgeInputErrors("\nError: Invalid Input\nPlease enter a positive integer for the number of intervals: ");
	}
	return intervals;
}

// Prompts user for schedule information and generates a vector of WIS objects using validated user input. Returns a vector of WIS objects, sorted by finish time
std::vector<WIS> generateWISVectorFromUserInput(int intervals) {
	std::vector<WIS> jobs;
	
	std::cout << "\nEnter Start time, Finish time, and Weight separated by a space:\nSi Fi Wi\n";

	// User populates each job
	int start, finish, profit;
	bool invalidEntryDetected = false;
	for (int i = 0; i < intervals; ++i) {
		// First check for valid input type
		if (!(std::cin >> start) || !(std::cin >> finish) || !(std::cin >> profit)) {
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
		std::cout << "\n*Please note that one or more entries were invalid and excluded from the data set\n";
	}

	// Sort by finish time
	std::sort(jobs.begin(), jobs.end(), compareByFinishTime);

	return jobs;
}

void printFormattedInputIntervals(const std::vector<WIS>& container) {
	std::cout << "\t" << std::left << std::setw(INDEX_WIDTH) <<
		"Index<i>" << std::setw(JOB_DETAILS_WIDTH) <<
		"S<i>" << std::setw(JOB_DETAILS_WIDTH) <<
		"F<i>" << std::setw(JOB_DETAILS_WIDTH) <<
		"W<i>\n";

	int numWISRecords = container.size();
	for (int i = 0; i < numWISRecords; ++i) {
		std::cout << "\t" <<
			std::setw(INDEX_WIDTH) << i + 1 <<
			std::setw(JOB_DETAILS_WIDTH) << container[i].getStartTime() <<
			std::setw(JOB_DETAILS_WIDTH) << container[i].getFinishTime() <<
			std::setw(JOB_DETAILS_WIDTH) << container[i].getProfit() << std::endl;
	}
}

void printOptimalSet(const std::vector<WIS>& container) {
	int length = container.size();
	if (length > 0) {
		container[0].printFormattedJob();
		for (int i = 1; i < length; ++i) {
			std::cout << ", ";
			container[i].printFormattedJob();
		}
	}
}

// Resets cin object to a useable state after an input error
void purgeInputErrors(std::string errorMessage) {
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cout << errorMessage;
}