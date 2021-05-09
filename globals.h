#ifndef __GLOBALS__
#define __GLOBALS__

#include <map>
#include <fstream>
#include <rude/config.h>

using namespace std;
using namespace rude;
extern map<int, string> g_optionMap;
extern ofstream g_logfile;
extern ofstream g_pidfile;

#endif //__GLOBALS__