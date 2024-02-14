#include <iostream>
#include "WISheader.h"

void WIS::printFormattedInterval() {
	std::cout << "(" << startTime << ", "
		<< finishTime << ", " << profit << ")\n";
}