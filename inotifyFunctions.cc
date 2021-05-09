#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/inotify.h>
#include <fstream>
#include <unistd.h>
#include "enum.h"
#include "globals.h"
#include <iostream>
#include "inotifyFunctions.h"

#define EVENT_SIZE (sizeof(struct inotify_event))
#define BUF_LEN (1024*(EVENT_SIZE+16))

#define BUFFER_SIZE 1024

int start_inotify(){
    int fd;
    int wd;
    char* buf = new char[BUF_LEN];

    fd = inotify_init();

    if(fd < 0){
        g_logfile << "inotify failed to init" << endl;
    }

    wd = inotify_add_watch(fd, g_optionMap[watchdir].c_str(), IN_CLOSE_WRITE);

    int len = BUF_LEN;
    ssize_t ret;
    while (len != 0 && (ret = read (fd, buf, len)) != 0) {
        if (ret == -1) {
            if (errno == EINTR)
            continue;
            perror ("read");
            break;
        }
        struct inotify_event *event = (struct inotify_event *) &buf[0];
        if(event->len){
            if(event->mask & IN_CLOSE_WRITE){
                if(event->mask & IN_ISDIR){
                    g_logfile << "The directory " << event->name << " was written and closed" << endl;
                }
                else{
                    g_logfile << "The file " << event->name << " was written and closed" << endl;
                    copyToVersions(event->name);
                }
            }
        }


        len -= ret;
        buf += ret;
    }
    (void) inotify_rm_watch(fd, wd);
    (void) close(fd);

    return 0;
}

std::string create_timestamp_filename(std::string filename){
    string timestamp;
    FILE *output_from_command;
    char tmpbuffer[BUFFER_SIZE];
    char *line_p;
    output_from_command = popen("date +\".%y.%m.%d-%H:%M:%S\"", "r");
    if(!output_from_command) return "";
    line_p = fgets(tmpbuffer, BUFFER_SIZE, output_from_command);
    while(line_p != NULL){
        timestamp = timestamp + line_p;
        line_p = fgets(tmpbuffer, BUFFER_SIZE, output_from_command);
    }
    pclose(output_from_command);
    
    return filename+timestamp;
}

int copyToVersions(std::string filename){
    string sourcePath = g_optionMap[watchdir] + "/"+filename;
    string destPath = g_optionMap[versionsDir] + "/" + create_timestamp_filename(filename);
    string command = "cp " + sourcePath + " " + destPath;
    system(command.c_str());
    return 0; 
}

