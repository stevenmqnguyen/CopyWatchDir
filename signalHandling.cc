/*
 * Filename	signalHandling.cc
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
#include <csignal> 
#include <stdlib.h>
#include "enum.h"
#include "globals.h"
#include "parseConfigFile.h"
#include "loggingFunctions.h"

using namespace std;

void signalHandler( int signum ){
    if(signum == SIGINT || signum == SIGTERM){
        g_pidfile.close();
        if(g_optionMap[verbose].compare("true") == 0){
            g_logfile << "Closed due to signal: " << (signum == SIGINT ? "SIGINT" : "SIGTERM") << endl;
        }
        g_logfile.close();
        if(PIDFileExists("./cs3377dirmond.pid")){
            system("rm ./cs3377dirmond.pid");
        }
        exit(0); 
    }
    else if(signum == SIGHUP){
        reparseConfig();
        if(g_optionMap[verbose].compare("true") == 0){
            g_logfile << "Reparsed config file due to signal: SIGHUP" << endl;
            g_logfile << "daemon_value: " << g_optionMap[daemon_value] << endl;
            g_logfile << "config_filename: " << g_optionMap[config_filename] << endl;
            g_logfile << "verbose: " << g_optionMap[verbose] << endl;
            g_logfile << "logfile_filename: " << g_optionMap[logfile_filename] << endl;
            g_logfile << "password: " << g_optionMap[password] << endl;
            g_logfile << "numVersions: " << g_optionMap[numVersions] << endl;
            g_logfile << "watchdir: " << g_optionMap[watchdir] << endl;
            //daemon_value, config_filename, verbose, logfile_filename, password, numVersions, watchdir
        }
    }
}