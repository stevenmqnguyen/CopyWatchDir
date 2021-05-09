#include <iostream>
#include <csignal> 
#include <stdlib.h>
#include "enum.h"
#include "globals.h"
#include "parseConfigFile.h"

using namespace std;

void signalHandler( int signum ){
    if(signum == SIGINT || signum == SIGTERM){
        g_pidfile.close();
        if(g_optionMap[verbose].compare("true") == 0){
            g_logfile << "Closed due to signal: " << (signum == SIGINT ? "SIGINT" : "SIGTERM") << endl;
        }
        g_logfile.close();
        system("rm cs3377dirmond.pid");
        exit(0); 
    }
    else if(signum == SIGHUP){
        reparseConfig();
        if(g_optionMap[verbose].compare("true") == 0){
            g_logfile << "Reparsed config file due to signal: SIGHUP" << endl;
            g_logfile << "daemon_value: " << g_optionMap[daemon_value];
            g_logfile << "config_filename: " << g_optionMap[config_filename];
            g_logfile << "verbose: " << g_optionMap[verbose];
            g_logfile << "logfile_filename: " << g_optionMap[logfile_filename];
            g_logfile << "password: " << g_optionMap[password];
            g_logfile << "numVersions: " << g_optionMap[numVersions];
            g_logfile << "watchdir: " << g_optionMap[watchdir];
            //daemon_value, config_filename, verbose, logfile_filename, password, numVersions, watchdir
        }
    }
}