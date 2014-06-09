#include <vector>

use namespace std;

class page
{
	protected:
	long inTick;
	long outTick;
	long pageNumber;
	int pageSize
	std vector<bool> bitmap;
	int type; //0 for code, 1 for read-write
	int delay;

	double timeRatio;
	double intensity;
	double breadth;

	public:
	page(long in, long out, long page, int pType = 0; int size=4096):
		inTick(in), outTick(out), pageNumber(page), type(pType)
		pageSize(size)
	{
		bitmap(pageSize, false);
		delay = 100 * pageSize/16;
	}
}

	
