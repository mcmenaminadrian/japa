#ifndef _PAGE_H_
#define _PAGE_H_


#define BUFFSZ 1024

class Page
{
	protected:
	const long inTick;
	const long outTick;
	const long pageNumber;
	const int pageSize
	std vector<bool> bitmap;
	int type; //1 code, 2 rw, 3 both
	const int delay;

	double timeRatio;
	double intensity;
	double breadth;
	long idleTime;
	long lastAccessed;

	public:
	Page(long& in, long& out, long& page, int& pType = 0; int& size=4096):
		inTick(in), outTick(out), pageNumber(page), type(pType)
		pageSize(size)
	{
		bitmap(pageSize, false);
		delay = 100 * pageSize/16;
		timeRatio = -1;
		intensity = -1;
		breadth = -1;
		lastAccessed = in - delay;
	}

	const long getIn() const { return inTick; }
	const long getOut() const { return outTick; }
	const long getStartIn() const { return inTick - delay; }

	const double getTimeRatio() const { return timeRatio;}
	const double getIntensity() const { return intensity;}
	const double getBreadth() const {return breadth;}
	const long getIdleTime() const {return idleTime;}
	const double getIdleRatio const { return (out - (in - delay))/idleTime;}

	void markByteUsed(const int byte);
	const double calculateIntensity();
	const double calculateTimeRatio();
	const double calculateBreadth();
};

#endif	
