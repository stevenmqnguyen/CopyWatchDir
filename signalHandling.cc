#include <iostream>
#include <csignal> 
#include "globals.h"
using namespace std;

void signalHandler( int signum ){
    if(signum == SIGINT || signum == SIGTERM){
        
    }
    else if(signum == SIGHUP){

    }
}