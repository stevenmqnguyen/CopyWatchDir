#include <iostream>
#include <string>
#include <map>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fstream>
#include <sys/stat.h>
#include <csignal>
#include "rude/config.h"
#include "tclap/CmdLine.h"
#include "enum.h"
#include "parseCommandLine.h"
#include "parseConfigFile.h"
#include "loggingFunctions.h"
#include "processControl.h"
#include "globals.h"
#include "signalHandling.h"

using namespace std;
using namespace rude;
using namespace TCLAP;

int main(int argc, char* argv[])
{
	signal(SIGINT, signalHandler);
	signal(SIGTERM, signalHandler);
	signal(SIGHUP, signalHandler);
	// TCLAP parse command line
	g_optionMap = parseCMD(argc, argv);

	// fill g_optionMap with configs
	parseConfig();
	
	
	processControl();

    return 0;
}






