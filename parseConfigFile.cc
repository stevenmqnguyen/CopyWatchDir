#include <map>
#include <string>
#include <iostream>
#include <stdlib.h>
#include "rude/config.h"
#include "parseConfigFile.h"
#include "enum.h"
#include "globals.h"

using namespace std;
using namespace rude;

void parseConfig(){
    Config config;
	if(config.load(g_optionMap[config_filename].c_str())){
		if(!config.setSection("Parameters", false)){
			cerr << "Config file is missing section: Parameters" << endl;
			exit(1);
		}
		if(config.exists("Verbose") 
		&& config.exists("LogFile") 
		&& config.exists("Password") 
		&& config.exists("NumVersions")
		&& config.exists("WatchDir")){
			g_optionMap[verbose] = config.getStringValue("Verbose");
			g_optionMap[logfile_filename] = config.getStringValue("LogFile");
			g_optionMap[password] = config.getStringValue("Password");
			g_optionMap[numVersions] = config.getStringValue("NumVersions");
			string dir = config.getStringValue("WatchDir");
			cout << dir << endl;
			size_t pos = dir.find_last_of("/");
			if(pos == dir.length()-1){
    			dir.erase(dir.length()-1);
			}
			cout << dir << endl;
			g_optionMap[watchdir] = dir;
		}
		else{
			cerr << "Config file is missing one or more definitions." << endl;
            exit(1);
		}
	}
	else{
		// loading the config file failed
		cout << "Error loading config file: " << config.getError() << endl;
        exit(1);
	}
}
void reparseConfig(){
    Config config;
	if(config.load(g_optionMap[config_filename].c_str())){
		if(!config.setSection("Parameters", false)){
			cerr << "Config file is missing section: Parameters" << endl;
			exit(1);
		}
		if(config.exists("Verbose") 
		&& config.exists("LogFile") 
		&& config.exists("Password") 
		&& config.exists("NumVersions")
		&& config.exists("WatchDir")){
			g_optionMap[verbose] = config.getStringValue("Verbose");
			g_optionMap[logfile_filename] = config.getStringValue("LogFile");
			//optionMap[password] = g_optionMap[password];
			g_optionMap[numVersions] = config.getStringValue("NumVersions");
			//optionMap[watchdir] = g_optionMap[watchdir];
		}
		else{
			cerr << "Config file is missing one or more definitions." << endl;
            exit(1);
		}
	}
	else{
		// loading the config file failed
		cout << "Error loading config file: " << config.getError() << endl;
        exit(1);
	}
}