#include <map>
#include <string>
#include <iostream>
#include <stdlib.h>
#include "rude/config.h"
#include "parseConfigFile.h"
#include "enum.h"

using namespace std;
using namespace rude;

rude::Config parseConfig(std::map<int,std::string> &optionMap){
    Config config;
	if(config.load(optionMap[config_filename].c_str())){
		if(!config.setSection("Parameters", false)){
			cerr << "Config file is missing section: Parameters" << endl;
			exit(1);
		}
		if(config.exists("Verbose") 
		&& config.exists("LogFile") 
		&& config.exists("Password") 
		&& config.exists("NumVersions")
		&& config.exists("WatchDir")){
			optionMap[verbose] = config.getStringValue("Verbose");
			optionMap[logfile_filename] = config.getStringValue("LogFile");
			optionMap[password] = config.getStringValue("Password");
			optionMap[numVersions] = config.getStringValue("NumVersions");
			optionMap[watchdir] = config.getStringValue("WatchDir");
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
    return config;
}
