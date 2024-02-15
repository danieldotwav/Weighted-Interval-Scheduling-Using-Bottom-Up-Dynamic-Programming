#include <iostream>
#include "WISheader.h"

void WIS::printFormattedInterval() const {
	std::cout << "(" << startTime << ", "
		<< finishTime << ", " << profit << ") ";
}