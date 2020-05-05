#include "../inc/private_irc.h"

t_client *s_find_client(t_env *e, int fd){
    t_client *run;

    if (!e || !e->clients)
        return NULL;
    run = e->clients;
    while (run){
        // ft_printf("current check fd: %d\n", run->fd);
        if (run->fd == fd)
            return (run);
        run = run->next;
    }
    return NULL;
}