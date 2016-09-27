#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
#include "rw.h"

#include <unistd.h> //getcwd
 
void get_ctl_value(int registr) {
    // return value dependency of registr
}

void clear_ctl_value() {
    // clear value
}

void set_ctl_value(* ctl_args) {
    // set to registr
}
 
int main(int argc, char *argv[]) {
    char* dir[1024];
    getcwd(dir, sizeof(dir));
    
    int value;
 
    switch (argv[0]) {
        case "read":
            get_ctl_value();
            break;
        case "write":
            set_ctl_value(arv[1]);
            break;
        case "clear":
            clear_ctl_value(arv[1]);
            break;
        default:
            fprintf(stderr, "Incorrect argument %s, see --help for more information.", argv[0]);
            break;
    }

    return 0;
} 
