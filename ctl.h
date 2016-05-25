#ifndef RW_IOCTL_H
#define RW_IOCTL_H
#include <linux/ioctl.h>
 
// typedef struct
// {
//     unsigned int value, registr;
// } ctl_args;
struct clt_args {
    unsigned int value, registr;
};
 
#define RW_GET_VARIABLES _IOR('q', 1, unsigned int *)
#define RW_CLR_VARIABLES _IO('q', 2)
#define RW_SET_VARIABLES _IOW('q', 3, ctl_args *)
 
#endif
