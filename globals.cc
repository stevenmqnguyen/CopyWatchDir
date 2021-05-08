#include <map>
#include <fstream>
#include <rude/config.h>
#include "globals.h"

using namespace std;
using namespace rude;

map<int, string> g_optionMap;
Config g_config;
ofstream g_logfile;
ofstream g_pidfile;