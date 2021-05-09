/*
 * Filename	loggingFunctions.cc
 * Date 	May 9, 2021
 * Author	Steven Nguyen
 * Email	steven.nguyen@utdallas.edu
 * Course	CS 3377.0W5 Spring 2021
 * Version 	1.0
 * Copyright	2021, All Rights Reserved
 *
 * Description
 * 	Daemon process that will watch a folder and respond to specific file operations that occur in that folder.
 *	The daemon will read its configuration parameters from a CONFIG file and then operate according to that configuration.
 *  When it detects a write, the daemon will immediately create a copy of the just written file and store that copy in a
 *  .versions subfolder. Each copy stored in the .versions subfolder will have a date stamp appended to the filename.
 *
 */
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