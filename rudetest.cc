// login.cpp
// Prompts for Username and Password
// Validates the user and returns the role of the user
//
//////////////////////////////////////

#include "rude/config.h"

#include <iostream>
#include <string>

using namespace std;
using namespace rude;

int main(void)
{

	std::string username;
	std::string password;

	// prompt user for login-name and password
	//
	cout << "Please enter your username:";
	cin >> username;
	cout << "Please enter your password:";
	cin >> password;

	// create a Config object
	//
	Config config;


	// Load the password config file
	//
	if(config.load("login.conf"))
	{
		// See if the username is valid
		//
		config.setSection("users");
		if( config.exists( username.c_str() ) )
		{
			// See if the password is valid
			//
			config.setSection("passwords");
			if(password == config.getStringValue(username.c_str()))
			{
				// determine the role of the user
				//
				config.setSection("roles");
				string role = config.getStringValue(username.c_str());
				cout << "You are logged in with " << role << " privileges\n";
				return 0;
			}
			else
			{
				// login failed
				//
				cout << "Invalid password: '" << password <<"'\n";
				cout << "Password should be: '" << config.getStringValue(username.c_str()) << "'\n";
				return 1;

			}
		}
		else
		{
			// login failed
			//
			cout << "Invalid username: '" << username <<"'\n";
			return 1;
		}


	}
	else
	{
		// loading the login config file failed
		//
		cout << "Error loading password file: " << config.getError() << "\n";
		return 1;
	}
}






