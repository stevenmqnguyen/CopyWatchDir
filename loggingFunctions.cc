#include <iostream>
#include <sys/stat.h>
#include <errno.h>

using namespace std;

bool PIDFileExists(const char* file) {
    struct stat buf;
    int code = stat(file, &buf);
    // cout << "Code: " << code << endl;
    // cout << errno << endl;
    // cout << EBADF << endl; // Error code 9
    // cout << ENOENT << endl; // Error code 2
    return code == -1 && (errno == EBADF || errno == ENOENT) ? false : true;
}