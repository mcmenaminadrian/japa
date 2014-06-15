#include <vector>
#include "page.hpp"

using namespace std;

const double Page::calculateIntensity()
{
	intensity = totalAccess/(pageSize * (outTick - (inTick - delay)));
	return intensity;
}

const double Page::calculateTimeRatio()
{
	timeRatio = delay / (outTick - inTick);
	return timeRatio;
}

const double Page::calculateBreadth()
{
	int bytesUsed = 0;
	for (int i = 0; i < pageSize; i++) {
		if (bitmap.at(i)) {
			bytesUsed++;
		}
	}
	breadth = bytesUsed / pageSize;
	return breadth;
}


