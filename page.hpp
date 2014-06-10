#ifndef _PAGE_H_
#define _PAGE_H_

class page
{
	protected:
	const long inTick;
	const long outTick;
	const long pageNumber;
	const int pageSize
	std vector<bool> bitmap;
	const int type; //0 for code, 1 for read-write
	const int delay;

	double timeRatio;
	double intensity;
	double breadth;

	public:
	page(long& in, long& out, long& page, int& pType = 0; int& size=4096):
		inTick(in), outTick(out), pageNumber(page), type(pType)
		pageSize(size)
	{
		bitmap(pageSize, false);
		delay = 100 * pageSize/16;
	}

	const long getIn() const { return inTick; }
	const long getOut() const { return outTick; }
	const long getStartIn() const { return inTick - delay; }

	const double getTimeRatio() const { return timeRatio;}
	const double getIntensity() const { return intensity;}
	const double getBreadth() const {return breadth;}

	void markByteUsed(const int byte);
	const double calculateIntensity();
	const double calculateTimeRatio();
	const double calculateBreadth();
};

#endif	
