#include <iostream>
#include <string>
#include <map>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fstream>
#include <sys/stat.h>
#include "rude/config.h"
#include "tclap/CmdLine.h"
#include "enum.h"
#include "parseCommandLine.h"
#include "parseConfigFile.h"
#include "loggingFunctions.h"
#include "processControl.h"

using namespace std;
using namespace rude;
using namespace TCLAP;

int main(int argc, char* argv[])
{
	// TCLAP parse command line
	map<int, string> optionMap = parseCMD(argc, argv);

	// create a Config object and fill optionMap with configs
	Config config = parseConfig(optionMap);
	
	// run program with fork
	// if(optionMap[daemon_value].compare("true") == 0){
	// 	pid_t forkvalue = fork();

	// 	// Error, no child created
	// 	if(forkvalue == -1){
	// 		cerr << "Error in fork. No child created." << endl;
	// 		exit(1);
	// 	}
	// 	// Child process
	// 	else if(forkvalue == 0){
	// 		cout << "This is the child process running!" << endl;
	// 		if(PIDFileExists("cs3377dirmond.pid")){
	// 			exit(1);
	// 		}
	// 		ofstream pidfile("cs3377dirmond.pid");
	// 		pidfile << getpid() << endl;
	// 		int i = 1;
	// 		while(true){
	// 			i++;
	// 		}
	// 	}
	// 	// Parent process
	// 	else{
	// 		cout << "This is the parent process running! Child PID: " << forkvalue << endl;
	// 		exit(0);
	// 	}

	// }
	// // Run program non daemon style (no forking)
	// else{
	// 	cout << "This is running without any daemons" << endl;
		
	// }
	processControl(optionMap);

    return 0;
}






