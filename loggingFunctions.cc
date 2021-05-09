#include <iostream>
#include <sys/stat.h>
#include <errno.h>

using namespace std;

bool PIDFileExists(const char* file) {
    struct stat buf;
    int code = stat(file, &buf);
    return code == -1 && (errno == EBADF || errno == ENOENT) ? false : true;
}

bool dirExists(const char* file) {
    struct stat buf;
    int code = stat(file, &buf);
    return code == -1 && (errno == EBADF || errno == ENOENT) ? false : true;
}