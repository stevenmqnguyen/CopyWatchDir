#include <iostream>
#include <csignal> 
#include <stdlib.h>
#include "globals.h"
#include "parseConfigFile.h"

using namespace std;

void signalHandler( int signum ){
    if(signum == SIGINT || signum == SIGTERM){
        g_pidfile.close();
        g_logfile << "Closed due to signal: " << (signum == SIGINT ? "SIGINT" : "SIGTERM") << endl;
        g_logfile.close();
        system("rm cs3377dirmond.pid");
        exit(0); 
    }
    else if(signum == SIGHUP){
        g_config = reparseConfig();
    }
}