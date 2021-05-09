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
    cout << "Before while loop" << endl;
    while (len != 0 && (ret = read (fd, buf, len)) != 0) {
        cout << "inside while loop" << endl;
        cout << "ret: " << ret << endl;
        cout << "len: " << len << endl;
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
                    cout << "The directory " << event->name << " was written and closed" << endl;
                }
                else{
                    g_logfile << "The file " << event->name << " was written and closed" << endl;
                    cout << "The file " << event->name << " was written and closed" << endl;
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