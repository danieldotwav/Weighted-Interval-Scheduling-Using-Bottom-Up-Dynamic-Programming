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
};

#endif