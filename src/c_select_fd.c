#include "../inc/private_irc_client.h"

int c_select_fd(const t_env_c *e){
    fd_set          read_fds;
    struct timeval  timeval;
    
    read_fds = e->active_fds;
    timeval.tv_sec = LISTEN_TIMEOUT;
    return(select((e->fd_max + 1), &read_fds, 0, 0, &timeval));
}