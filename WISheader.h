#ifndef WISHEADER_H
#define WISHEADER_H

class WIS {
private:
	int startTime;
	int finishTime;
	int profit;

public:
	WIS() : startTime(0), finishTime(0), profit(0) {}
	WIS(int start, int finish, int weight) : startTime(start), finishTime(finish), profit(weight) {}
	
	void setStartTime(int start) { startTime = start; }
	void setFinishTime(int finish) { finishTime = finish; }
	void setProfit(int weight) { profit = weight; }
	
	int getStartTime() const { return startTime; }
	int getFinishTime() const { return finishTime; }
	int getProfit() const { return profit; }
	void printFormattedInterval();
};

#endif