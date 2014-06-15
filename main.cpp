#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <cstring>
#include "page.hpp"
#include <expat.h>


#define OUTLIMIT 100000000

using namespace std;

static long tickCount = OUTLIMIT;
static XML_Parser *pp_ctrl;
static string ticker;
static multimap<long, Page*> processedPages;
static void XMLCALL
closeHandler(void* data, const XML_Char *name);

void usage()
{
	cout << "japa - just another paging analyser\n";
	cout << "Basic usage:\n";
	cout << "\tjapa inputfile\n";
	cout << "Options:\n";
	cout << "\t-i\t\tIntensity (default)\n";
	cout << "\t-ni\t\tDo not measure intensity\n";
	cout << "\t-?\t\tShow this usage message\n";
	return;
}

static void XMLCALL
tickHandler(void *data, const XML_Char *s, int len)
{
	//we add the data here but only process in end handler
	ticker.append(s, len);
}

static void XMLCALL
referenceHandler(void* data, const XML_Char *name, const XML_Char **attr)
{
	Page *addPage = static_cast<Page *>(data);
	long address;
	int size;
	if (strcmp(name, "code") == 0) {
		addPage->setType(1);
	} else {
		addPage->setType(2);
	}
	for (int i = 0; attr[i]; i+=2) {
		if (strcmp(attr[i], "address") == 0) {
			address = atol(attr[i + 1]);
			continue;
		}
		if (strcmp(attr[i], "size") == 0) {
			size = atoi(attr[i + 1]);
		}
	}
	for (int i = 0; i < size; i++) {
		addPage->markByteUsed(i + address);
	}
	ticker.clear();
}


static void XMLCALL
intensityHandler(void* data, const XML_Char *name, const XML_Char **attr)
{
	long in, out, frame;
	if (strcmp(name, "page") == 0) {
		for (int i = 0; attr[i]; i+=2) {
			if (strcmp(attr[i], "frame") == 0) {
				frame = atol(attr[i + 1]);
				continue;
			}
			if (strcmp(attr[i], "in") == 0) {
				in = atol(attr[i + 1]);
				if (in > tickCount) {
					cout << "Reached tick " << in << "\n";
					tickCount += OUTLIMIT;
				}
				continue;
			}
			if (strcmp(attr[i], "out") == 0) {
				out = atol(attr[i + 1]);
			}
		}
		Page *addPage = new Page(in, out, frame);
		//set new handlers
		XML_SetUserData(*pp_ctrl, addPage);
		XML_SetStartElementHandler(*pp_ctrl, referenceHandler);
		XML_SetCharacterDataHandler(*pp_ctrl, tickHandler);
	}
}

static void XMLCALL closeHandler(void* data, const XML_Char *name)
{
	Page *addPage = static_cast<Page *>(data);
	if (strcmp(name, "code") == 0 || strcmp(name, "rw") == 0) {
		long tickTime = atol(ticker.c_str());
		addPage->updateIdleTime(tickTime);
	} else if (strcmp(name, "page") == 0) {
		//add and reset
		processedPages.insert(
			pair<long, Page *>(addPage->getIn(), addPage));
		XML_SetStartElementHandler(*pp_ctrl, intensityHandler);
		XML_SetCharacterDataHandler(*pp_ctrl, NULL);
	}
}


int main(int argc, char *argv[])
{
	bool intensity = true; //default use case
	bool breadth = false;
	char *xmlFile;
	FILE *inXML;
	size_t len = 0;
	char data[BUFFSZ];
	int done;
	
	if (argc < 2) {
		usage();
		return 1;
	}

	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-i") == 0) {
			intensity = true;
		}
		if (strcmp(argv[i], "-ni") == 0) {
			intensity = false;
		}
		if (strcmp(argv[i], "-?") == 0) {
			usage();
			exit(0);
		}
	}

	xmlFile = argv[argc - 1];

	XML_Parser p_ctrl = XML_ParserCreate("UTF-8");
	if (!p_ctrl) {
		cout << "Could not create XML parser.\n";
		return 1;
	}
	pp_ctrl = &p_ctrl;

	if (intensity) {
		cout << "Starting process\n";
		XML_SetStartElementHandler(p_ctrl, intensityHandler);
		XML_SetEndElementHandler(p_ctrl, closeHandler);
		inXML = fopen(xmlFile, "r");
		if (!inXML) {
			cout << "ERROR: could not open ";
			cout << xmlFile;
			XML_ParserFree(p_ctrl);
			return 1;
		}

		do {
			len = fread(data, 1, sizeof(data), inXML);
			done = len < sizeof(data);
			if (XML_Parse(p_ctrl, data, len, 0) == 0) {
				enum XML_Error errcode =
					XML_GetErrorCode(p_ctrl);
				cout << "ERROR: " << XML_ErrorString(errcode);
				cout << "\n";
				cout << "Error at line, column ";
				cout << XML_GetCurrentLineNumber(p_ctrl);
				cout << ",";
				cout << XML_GetCurrentColumnNumber(p_ctrl);
				cout << "\n";
				XML_ParserFree(p_ctrl);
				return 1;
			}
		} while(!done);
	}

	pp_ctrl = NULL;
	XML_ParserFree(p_ctrl);
	fclose(inXML);

	//now process the pages
	multimap<long, Page*>::iterator processIT;
	for (processIT = processedPages.begin();
		processIT != processedPages.end(); processIT++) {
		double intensity = processIT->second->calculateIntensity();
		double breadth = processIT->second->calculateBreadth();
		double timeRatio = processIT->second->calculateTimeRatio();
		cout << "Intensity: " << intensity << " , Breadth: ";
		cout << breadth << " , Time Ratio: " << timeRatio << "\n";
	}

	return 0;
}

