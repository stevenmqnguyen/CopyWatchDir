#include <iostream>
#include <string>
#include <map>
#include <stdlib.h>
#include "rude/config.h"
#include "tclap/CmdLine.h"
#include "enum.h"
#include "parseCommandLine.h"
#include "parseConfigFile.h"

using namespace std;
using namespace rude;
using namespace TCLAP;

int main(int argc, char* argv[])
{
	// TCLAP parse command line
	map<int, string> optionMap = parseCMD(argc, argv);

	// create a Config object
	Config config = parseConfig(optionMap);

	cout << optionMap[verbose] << endl;
	cout << optionMap[logfile] << endl;
	cout << optionMap[password] << endl;
	cout << optionMap[numVersions] << endl;
	cout << optionMap[watchdir] << endl;
    return 0;
}






