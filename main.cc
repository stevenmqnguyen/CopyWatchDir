#include <iostream>
#include <string>
#include <map>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fstream>
#include <sys/stat.h>
#include "rude/config.h"
#include "tclap/CmdLine.h"
#include "enum.h"
#include "parseCommandLine.h"
#include "parseConfigFile.h"
#include "loggingFunctions.h"
#include "processControl.h"
#include "globals.h"

using namespace std;
using namespace rude;
using namespace TCLAP;

int main(int argc, char* argv[])
{
	// TCLAP parse command line
	g_optionMap = parseCMD(argc, argv);

	// create a Config object and fill optionMap with configs
	g_config = parseConfig();
	
	
	processControl();

    return 0;
}






