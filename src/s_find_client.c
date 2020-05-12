#include "../inc/private_irc.h"

t_client *s_find_client(t_env_s *e, int fd){
    t_client *run;

    if (!e || !e->clients)
        return NULL;
    run = e->clients;
    while (run){
        if (run->fd == fd)
            return (run);
        run = run->next;
    }
    return NULL;
}