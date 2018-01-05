#ifndef _PAGE_H_
#define _PAGE_H_


#define BUFFSZ 1024

class Page
{
	protected:
	const long inTick;
	const long outTick;
	const long pageNumber;
	const int pageSize;
	std::vector<bool> bitmap;
	int type; //1 code, 2 rw, 3 both
	double delay;
	long totalAccess;

	double timeRatio;
	double intensity;
	double breadth;
	long idleTime;
	long lastAccessed;

	public:
	Page(long in, long out, long page, int size=4096, int pType = 0):
		inTick(in), outTick(out), pageNumber(page),
		pageSize(size), type(pType)
	{
		bitmap.resize(pageSize, false);
		delay = 100 * pageSize/16;
		timeRatio = 0;
		intensity = 0;
		breadth = 0;
		lastAccessed = in - delay;
		totalAccess = 0;
		idleTime = 0;
	}

	void setType(int ty) { type |= ty; }
	const int getType() const { return type; }
	const long getPageNumber() const { return pageNumber; }

	const long getIn() const { return inTick; }
	const long getOut() const { return outTick; }
	const long getStartIn() const { return inTick - delay; }

	const double getTimeRatio() const { return timeRatio;}
	const double getIntensity() const { return intensity;}
	const double getBreadth() const {return breadth;}
	const long getIdleTime() const {return idleTime;}
	const double getIdleRatio() const
		{ return (outTick - (inTick - delay))/idleTime;}
	void updateIdleTime(long tickNumber);
	void markByteUsed(const long byteIn) {
		long offset = byteIn & 0xFFF;
		bitmap.at(offset) = true;
	}
	const double calculateIntensity();
	const double calculateTimeRatio();
	const double calculateBreadth();
};

#endif	
