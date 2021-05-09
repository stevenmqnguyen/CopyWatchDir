/*
 * Filename	processControl.cc
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
#include "processControl.h"
#include <string>
#include <map>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fstream>
#include <sys/stat.h>
#include <cstdlib>
#include "loggingFunctions.h"
#include "enum.h"
#include "rude/config.h"
#include "globals.h"
#include "inotifyFunctions.h"

using namespace std;
using namespace rude;

int processControl(){
	// run program with fork
	if(g_optionMap[daemon_value].compare("true") == 0){
		pid_t forkvalue = fork();
		
        // Error, no child created
		if(forkvalue == -1){
            // Create logfile
            g_logfile.open(g_optionMap[logfile_filename].c_str(), std::ios_base::app);
			g_logfile << "Error in fork. No child created." << endl;
            g_logfile.close();
			exit(1);
		}
		// Child process
		else if(forkvalue == 0){
			childProcess();
		}
		// Parent process
		else{
            parentProcess();
		}
	}
	// Run program non daemon style (no forking)
	else{
        defaultProcess();
	}
    return 0;
}

int childProcess(){
    // Create logfile
    g_logfile.open(g_optionMap[logfile_filename].c_str(), std::ios_base::app);
    if(g_optionMap[verbose].compare("true") == 0){
        g_logfile << "Childproccess has commenced..." << endl;    
    }
    if(PIDFileExists("./cs3377dirmond.pid")){
        g_logfile << "cs3377dirmond.pid already exists.\nOnly one cs3377dirmond is able to run at a time. \nexiting." << endl;
        exit(1);
    }
    g_pidfile.open("./cs3377dirmond.pid");
    g_pidfile << getpid() << endl;

    if(!dirExists(g_optionMap[versionsDir].c_str())){
        // create .versions folder
        g_logfile << ".versions folder doesn't exist, creating..." << endl;
        system(("mkdir "+g_optionMap[versionsDir]).c_str());
    }
    start_inotify();

    g_pidfile.close();
    if(PIDFileExists("./cs3377dirmond.pid")){
        system("rm ./cs3377dirmond.pid");
    } 
    g_logfile.close();
    exit(0);
    return 0;
}

int parentProcess(){
    exit(0);
    return 0;
}

int defaultProcess(){
    g_logfile.open(g_optionMap[logfile_filename].c_str(), std::ios_base::app);
    if(g_optionMap[verbose].compare("true") == 0){
        g_logfile << "Running program without any daemons" << endl;
    }
    if(!dirExists(g_optionMap[versionsDir].c_str())){
        // create .versions folder
        g_logfile << ".versions folder doesn't exist, creating..." << endl;
        system(("mkdir "+g_optionMap[versionsDir]).c_str());
    }


    start_inotify();
    g_logfile.close();
    return 0;
}