#ifndef __INOTIFYFUNCTIONS__
#define __INOTIFYFUNCTIONS__

int start_inotify();
std::string create_timestamp_filename(std::string filename);
int copyToVersions(std::string filename);

#endif //__INOTIFYFUNCTIONS