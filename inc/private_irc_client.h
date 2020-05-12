#ifndef PRIVATE_IRC_CLIENT_H
#define PRIVATE_IRC_CLIENT_H

#include "./private_irc.h"

//DATA STRUCTURES
typedef struct  s_server_c{
    int                 fd;
    char                ip_address[INET6_ADDRSTRLEN];

    struct s_server_c  *next;
    struct s_server_c  *prev;

}               t_server_c;

typedef struct      s_env_c {
    fd_set          server_fds;
    fd_set          read_fds;
    int             fd_max;
    t_server_c      *servers;
}                   t_env_c;

int                 c_bind(const char *address, const char *port);
void                c_getinput(int fd);
void                c_select_fd(t_env_c *e);
void                c_connection_new(t_env_c *e, int fd, const char *address);
t_server_c          *c_find_server(t_env_c *e, int fd);
void                c_connection_rmv(t_env_c *e, int fd);

#endif