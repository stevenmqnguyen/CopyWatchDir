#ifndef __PROCESSCONTROL__
#define __PROCESSCONTROL__
#include<string>
#include<map>

int processControl(std::map<int,std::string> &optionMap);
int childProcess(std::map<int,std::string> &optionMap);
int parentProcess();
int defaultProcess();

#endif //__PROCESSCONTROL__