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
	optionMap[daemon] = daemonSwitch.getValue() ? "true" : "false";
    optionMap[config_filename] = configArg.getValue();

    return optionMap;
}