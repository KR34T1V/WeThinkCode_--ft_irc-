#include "../inc/private_irc_client.h"

void    c_select_fd( t_env_c *e){
    int             rtn;
    struct timeval  timeval;
    
    e->read_fds = e->server_fds;
    timeval.tv_sec = LISTEN_TIMEOUT;
    rtn = select((e->fd_max + 1), &e->read_fds, 0, 0, &timeval);
    if (rtn < 0){
        perror("select");
        exit(5);
    }
}