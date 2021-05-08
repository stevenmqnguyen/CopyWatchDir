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

using namespace std;
using namespace rude;

int processControl(){
	// run program with fork
	if(g_optionMap[daemon_value].compare("true") == 0){
		pid_t forkvalue = fork();
		
        // Error, no child created
		if(forkvalue == -1){
            // Create logfile
            g_logfile.open(g_optionMap[logfile_filename].c_str());
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
    g_logfile.open(g_optionMap[logfile_filename].c_str());
    cout << "This is the child process running!" << endl;
    if(PIDFileExists("cs3377dirmond.pid")){
        g_logfile << "cs3377dirmond.pid already exists.\nOnly one cs3377dirmond is able to run at a time. \nexiting." << endl;
        exit(1);
    }
    g_pidfile.open("cs3377dirmond.pid");
    g_pidfile << getpid() << endl;

    g_pidfile.close();
    system("rm cs3377dirmond.pid");
    g_logfile.close();
    exit(0);
    return 0;
}

int parentProcess(){
    cout << "This is the parent process running! " << endl;
    exit(0);
    return 0;
}

int defaultProcess(){
    cout << "This is running without any daemons" << endl;
    return 0;
}