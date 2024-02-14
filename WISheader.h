#ifndef WISHEADER_H
#define WISHEADER_H

class WIS {
private:
	int startTime;
	int finishTime;
	int weight;

public:
	WIS();
	WIS(int start, int finish, int w);
	
	void setStartTime(int start) { startTime = start; }
	void setFinishTime(int finish) { finishTime = finish; }
	void setWeight(int w) { weight = w; }
};

#endif