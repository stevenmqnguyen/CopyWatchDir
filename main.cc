// login.cpp
// Prompts for Username and Password
// Validates the user and returns the role of the user
//
//////////////////////////////////////

#include "rude/config.h"
#include "tclap/CmdLine.h"
#include <iostream>
#include <string>
#include <map>

using namespace std;
using namespace rude;
using namespace TCLAP;
int main(int argc, char* argv[])
{
	// TCLAP Stuff
	enum cla{daemon, config_filename};
    CmdLine cmd("cs3377dirmond Directory Monitor Daemon", ' ', "1.0");
    SwitchArg daemonSwitch("d", "daemon", "Run in daemon mode (forks to run as a daemon)", cmd, false);
    UnlabeledValueArg<string> configArg("config_filename", "The name of the configuration file. Defaults to cs3377dirmond.conf", true, "cs3377dirmond.conf", "config filename", false);
    cmd.add(configArg);
    cmd.parse(argc, argv); 

    map<int, string> optionMap;
	optionMap[daemon] = daemonSwitch.getValue() ? "true" : "false";
    optionMap[config_filename] = configArg.getValue();

	cout << optionMap[daemon] << endl;
	cout << optionMap[config_filename] << endl;


	// create a Config object
	//
	Config config;


	// // Load the password config file
	// //
	// if(config.load("login.conf"))
	// {
	// 	// See if the username is valid
	// 	//
	// 	config.setSection("users");
	// 	if( config.exists( username.c_str() ) )
	// 	{
	// 		// See if the password is valid
	// 		//
	// 		config.setSection("passwords");
	// 		if(password == config.getStringValue(username.c_str()))
	// 		{
	// 			// determine the role of the user
	// 			//
	// 			config.setSection("roles");
	// 			string role = config.getStringValue(username.c_str());
	// 			cout << "You are logged in with " << role << " privileges\n";
	// 			return 0;
	// 		}
	// 		else
	// 		{
	// 			// login failed
	// 			//
	// 			cout << "Invalid password: '" << password <<"'\n";
	// 			cout << "Password should be: '" << config.getStringValue(username.c_str()) << "'\n";
	// 			return 1;

	// 		}
	// 	}
	// 	else
	// 	{
	// 		// login failed
	// 		//
	// 		cout << "Invalid username: '" << username <<"'\n";
	// 		return 1;
	// 	}


	// }
	// else
	// {
	// 	// loading the login config file failed
	// 	//
	// 	cout << "Error loading password file: " << config.getError() << "\n";
	// 	return 1;
	// }
    return 0;
}






