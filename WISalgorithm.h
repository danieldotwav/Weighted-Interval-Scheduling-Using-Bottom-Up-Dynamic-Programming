#ifndef WISALGORITHM_H
#define WISALGORITHM_H

#include "WISheader.h";
#include <vector>

// === Main Algorithm Functions ===
std::vector<WIS> getOptimalSet(const std::vector<WIS>& jobs);
int findLastNonConflictingJob(const std::vector<WIS>& jobs, int index);
bool isValidWISParameters(int start, int finish, int profit);
bool compareByFinishTime(const WIS& firstJob, const WIS& secondJob);

// === Utility Functions ===
void printFormattedInputIntervals(const std::vector<WIS> container);
void purgeInputErrors(std::string errorMessage);

#endif