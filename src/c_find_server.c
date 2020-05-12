#include "../inc/private_irc_client.h"

t_server_c  *c_find_server(t_env_c *e, int fd){
    t_server_c  *run;

    for (run = e->servers; run; run = run->next){
        if (run->fd == fd)
            return (run);
    }
    return (NULL);
}