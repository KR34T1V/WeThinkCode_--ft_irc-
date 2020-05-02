#include "../inc/private_irc.h"

void s_rmv_client(t_env *e, int fd){
    t_client *client;

    if((client = s_find_client(e, fd))){
        if (client->next)
            client->next->prev = client->prev;
        if (client->prev)
            client->prev->next = client->next;
        if (client == e->clients)
            e->clients = client->next;
        client->next = NULL;
        client->prev = NULL;
        ft_memdel((void **)&client);
    }
}