#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h> 
#include <unistd.h>
#include <assert.h>
#include <fcntl.h>
#include <sys/time.h>
#include <time.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>
#include <signal.h>
#include <dirent.h>
#include <sys/inotify.h>



int main (int argc, char** argv) {

    assert(argc == 2);

    char* dir_name = argv[1];

    int fd = inotify_init();
    if (fd < 0) {
        perror("Error in init(): ");
        exit(-1);
    }

    uint32_t mask = IN_CREATE | IN_DELETE | IN_MOVE_SELF;
    char buf[BUFSIZ] = {};

    int watch = inotify_add_watch(fd, dir_name, mask);
    if (watch < 0) {
        perror("Error in adding watch(): ");
        exit(-1);
    }

    struct inotify_event* event;
    //event = (struct inotify_event*) buf;

    while (1) {
        int resop = read(fd, buf, BUFSIZ);
        printf("Bytes read: %d\n", resop);
        if (resop > 0) {

            printf("Events read: %ld\n", resop / sizeof(struct inotify_event));
            // event = (struct inotify_event*) buf;
            // printf("Path: %s ", event->name);

            for (char* event_data = buf; event_data < buf + BUFSIZ; event_data += sizeof(struct inotify_event)) {
            event = (struct inotify_event*) event_data;
                if (event->mask == IN_CREATE) {
                    printf("Dir created\n");
                } else if (event->mask == IN_DELETE) {
                    printf("Dir deleted\n");
                } else if (event->mask == IN_MOVE_SELF) {
                    printf("Dir moved\n");
                }
            }
        } else {
            perror("Read not succesfull\n");
            exit(-1);
        }
    }

    close(fd);

    return 0;
}