#ifndef PRIVATE_IRC_CLIENT_H
#define PRIVATE_IRC_CLIENT_H

#include "./private_irc.h"

//DATA STRUCTURES
typedef struct  s_env_c {
    fd_set      active_fds;
    int         fd_max;
}               t_env_c;


void                c_getinput(int fd);

#endif