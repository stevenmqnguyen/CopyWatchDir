#include <map>
#include <fstream>
#include <rude/config.h>

using namespace std;
using namespace rude;

map<int, string> g_optionMap;
ofstream g_logfile;
ofstream g_pidfile;