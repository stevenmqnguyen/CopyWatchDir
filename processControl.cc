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
using namespace std;

int processControl(std::map<int,std::string> &optionMap){
	// run program with fork
	if(optionMap[daemon_value].compare("true") == 0){
		pid_t forkvalue = fork();
		
        // Error, no child created
		if(forkvalue == -1){
            // Create logfile
            ofstream logfile(optionMap[logfile_filename].c_str());
			logfile << "Error in fork. No child created." << endl;
            logfile.close();
			exit(1);
		}
		// Child process
		else if(forkvalue == 0){
			childProcess(optionMap);
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

int childProcess(std::map<int,std::string> &optionMap){
    // Create logfile
    ofstream logfile(optionMap[logfile_filename].c_str());
    cout << "This is the child process running!" << endl;
    if(PIDFileExists("cs3377dirmond.pid")){
        logfile << "cs3377dirmond.pid already exists.\nOnly one cs3377dirmond is able to run at a time. \nexiting." << endl;
        exit(1);
    }
    ofstream pidfile("cs3377dirmond.pid");
    pidfile << getpid() << endl;

    pidfile.close();
    system("rm cs3377dirmond.pid");
    logfile.close();
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