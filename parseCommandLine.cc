/*
 * Filename	parseCommandLine.cc
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
#include "tclap/CmdLine.h"
#include <iostream>
#include <string>
#include <map>
#include "enum.h"

using namespace std;
using namespace TCLAP;

map<int,string> parseCMD(int argc, char* argv[]){
	// TCLAP Stuff
    CmdLine cmd("cs3377dirmond Directory Monitor Daemon", ' ', "1.0");
    SwitchArg daemonSwitch("d", "daemon", "Run in daemon mode (forks to run as a daemon)", cmd, false);
    UnlabeledValueArg<string> configArg("config_filename", "The name of the configuration file. Defaults to cs3377dirmond.conf", true, "cs3377dirmond.conf", "config filename", false);
    cmd.add(configArg);
    cmd.parse(argc, argv); 

	// Create map to hold TCLAP and RudeConfig stuff
    map<int, string> optionMap;
	optionMap[daemon_value] = daemonSwitch.getValue() ? "true" : "false";
    optionMap[config_filename] = configArg.getValue();

    return optionMap;
}