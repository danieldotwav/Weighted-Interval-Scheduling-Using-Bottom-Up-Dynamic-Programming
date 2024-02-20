#include "WISheader.h";
#include "WISalgorithm.h";
#include <iomanip>

const int INDEX_WIDTH = 15;
const int JOB_DETAILS_WIDTH = 10;

// === Main Algorithm Functions ===

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

	std::cout << "\nMaximum profit of non-overlapping scheduling is " << maxProfit;

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

void printFormattedInputIntervals(const std::vector<WIS> container) {
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

// Resets cin object to a useable state after an input error
void purgeInputErrors(std::string errorMessage) {
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cout << errorMessage;
}