#include <vector>
#include "page.hpp"

using namespace std;

const double Page::calculateIntensity()
{
	double doubleDelay = static_cast<double>(delay);
	intensity =
		totalAccess/(pageSize * (outTick - (inTick - doubleDelay)));
	return intensity;
}

const double Page::calculateTimeRatio()
{
	double doubleDelay = static_cast<double>(delay);
	timeRatio = (doubleDelay + idleTime) / (outTick - inTick);
	return timeRatio;
}

const double Page::calculateBreadth()
{
	double bytesUsed = 0;
	for (int i = 0; i < pageSize; i++) {
		if (bitmap.at(i)) {
			bytesUsed++;
		}
	}
	breadth = bytesUsed / pageSize;
	return breadth;
}


