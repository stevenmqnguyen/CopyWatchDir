/*
 * Filename	main.cc
 * Date 	May 9, 2021
 * Author	Steven Nguyen
 * Email	steven.nguyen@utdallas.edu
 * Course	CS 3377.0W5 Spring 2021
 * Version 	1.0
 * Copyright	2021, All Rights Reserved
 *
 * Description
 * 	Daemon process that will watch a folder and respond to specific file operations that occur in that folder.
 *	The daemon will read its configuration parameters from a CONFIG file and then operate according to that configuration.
 *  When it detects a write, the daemon will immediately create a copy of the just written file and store that copy in a
 *  .versions subfolder. Each copy stored in the .versions subfolder will have a date stamp appended to the filename.
 *
 */
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






