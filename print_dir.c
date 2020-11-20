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


int main (int argc, char** argv) {

    assert(argc == 2);

    char* dir_path = argv[1];
    
    DIR* directory = opendir(dir_path);
    if (directory == NULL) {
         perror("Error in opendir(): ");
    }

    errno = 0;
    struct dirent* entry = readdir(directory);
    while (( entry = readdir(directory) ) != NULL) {
        char* entry_name = entry->d_name;
        printf("%s\n", entry_name);
    }


    closedir(directory);





    return 0;
}