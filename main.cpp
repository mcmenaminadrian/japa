#include <iostream>
#include "page.hpp"
#include "expat.h"

use namespace std;

static XML_Parser *p_ctrl

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
referenceHandler(void* data, const XML_Char *name, const XML_Char **attr)
{
	Page *addPage = static_cast<Page *>(data);
	int type = 0;
	long address;
	int size;
	if (strcmp(name, "code") == 0) {
		addPage->type &= 1;
	} else {
		addPage->type &= 2;
	}
	for (int i = 0; attr[i]; i+=2) {
		if (strcmp(attr[i], address) == 0) {
			address = atol(attr[i + 1]);
			continue;
		}
		if (strcmp(attr[i], size) == 0) {
			size = atoi(attr[i + 1]);
		}
	}
	for (i = 0; i < size; i++) {
		addPage->bitmap(i + address) = true;
	}
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
				continue;
			}
			if (strcmp(attr[i], "out") == 0) {
				out = atol(attr[i + 1]);
			}
		}
		Page *addPage = new Page(in, out, frame);
		//set new handler
		XML_SetUserData(p_ctrl, addPage);
		XML_SetStartElementHandler(p_ctrl, referenceHandler);

int main(int argc, char *argv[])
{
	bool intensity = true; //default use case
	bool breadth = false;
	char *xmlFile;
	FILE *inXML;
	size_t len = 0;
	char data[BUFFSZ];
	
	if (argc < 2) {
		usage();
		return 1;
	}

	for (int i = 1; i < argc; i++) {
		if ((strcmp(argv[i], "-i") == 0) {
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

	p_ctrl = XML_ParserCreate("UTF-8");
	if (p_ctrl) {
		cout << "Could not create XML parser.\n";
		return 1;
	}

	if (intensity) {
		XML_SetStartElementHandler(p_ctrl, intensityHandler);
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
				enum XML_Error = XML_GetErrorCode(p_ctrl);
				cout << "ERROR: " << XML_ErrorString(errcode);
				cout << "\n";
				cout << "Error at line, column ";
				cout << XML_GetCurrentLineNumber(p_ctrl);
				cout << ",";
				cout << XML_GetCurrentColumnNumber(p_ctrl);
				cout << XML_ParserFree(p_ctrl) << "\n";
				return 1;
			}
		} while(!done);
	}

	XML_ParserFree(p_ctrl);
	fclose(inXML);

	return 0;
}

