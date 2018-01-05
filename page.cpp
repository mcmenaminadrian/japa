#include <vector>
#include "page.hpp"

using namespace std;

const double Page::calculateIntensity()
{
	double doubleDelay = static_cast<double>(delay);
	intensity = totalAccess;
	double intenseFactor =pageSize * (outTick - (inTick - doubleDelay));
	intensity /= intenseFactor;
	return intensity;
}

const double Page::calculateTimeRatio()
{
	idleTime += (outTick - lastAccessed);
	timeRatio = idleTime;
	double timeDiff = outTick - (inTick - delay);
	timeRatio /= timeDiff;
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
	breadth = bytesUsed; // / pageSize;
	return breadth;
}

void Page::updateIdleTime(long tickNumber) {
	idleTime += ((tickNumber - 1) - lastAccessed);
	lastAccessed = tickNumber;
	totalAccess++;
}



