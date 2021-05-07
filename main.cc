// login.cpp
// Prompts for Username and Password
// Validates the user and returns the role of the user
//
//////////////////////////////////////

#include "rude/config.h"
#include "tclap/CmdLine.h"
#include <iostream>
#include <string>
#include <map>

using namespace std;
using namespace rude;
using namespace TCLAP;
int main(int argc, char* argv[])
{
	// TCLAP Stuff
	enum cla{daemon, config_filename, verbose, logfile, password, numVersions, watchdir};
    CmdLine cmd("cs3377dirmond Directory Monitor Daemon", ' ', "1.0");
    SwitchArg daemonSwitch("d", "daemon", "Run in daemon mode (forks to run as a daemon)", cmd, false);
    UnlabeledValueArg<string> configArg("config_filename", "The name of the configuration file. Defaults to cs3377dirmond.conf", true, "cs3377dirmond.conf", "config filename", false);
    cmd.add(configArg);
    cmd.parse(argc, argv); 

	// Create map to hold TCLAP and RudeConfig stuff
    map<int, string> optionMap;
	optionMap[daemon] = daemonSwitch.getValue() ? "true" : "false";
    optionMap[config_filename] = configArg.getValue();


	// create a Config object
	Config config;

	// Load the parameters config file
	if(config.load(optionMap[config_filename].c_str())){
		if(!config.setSection("Parameters", false)){
			cerr << "Config file is missing section: Parameters" << endl;
			return 1;
		}
		if(config.exists("Verbose") 
		&& config.exists("LogFile") 
		&& config.exists("Password") 
		&& config.exists("NumVersions")
		&& config.exists("WatchDir")){
			optionMap[verbose] = config.getStringValue("Verbose");
			optionMap[logfile] = config.getStringValue("LogFile");
			optionMap[password] = config.getStringValue("Password");
			optionMap[numVersions] = config.getStringValue("NumVersions");
			optionMap[watchdir] = config.getStringValue("WatchDir");
		}
		else{
			cerr << "Config file is missing one or more definitions." << endl;
			return 1;
		}
	}
	else{
		// loading the login config file failed
		cout << "Error loading config file: " << config.getError() << endl;
		return 1;
	}
	cout << optionMap[verbose] << endl;
	cout << optionMap[logfile] << endl;
	cout << optionMap[password] << endl;
	cout << optionMap[numVersions] << endl;
	cout << optionMap[watchdir] << endl;
    return 0;
}






