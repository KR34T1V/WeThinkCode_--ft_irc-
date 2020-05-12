#include "../inc/private_irc_server.h"

t_client *s_find_nick(t_env_s *e, char *nick){
    t_client *run;

    if (!e || !nick)
        return (NULL);
    run = e->clients;
    while (run){
        if (ft_strequ(run->nick, nick))
            return run;
        run = run->next;
    }
    return NULL;
}