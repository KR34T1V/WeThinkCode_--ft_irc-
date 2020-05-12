#include "../inc/private_irc_server.h"

void s_rmv_client(t_env_s *e, int fd){
    t_client *client;

    if((client = s_find_client(e, fd))){
        ft_printf("IRC Server: %s on %s disconnected from socket %d\n",client->nick, client->ip_address, client->fd);
        if (client->next)
            client->next->prev = client->prev;
        if (client->prev)
            client->prev->next = client->next;
        if (client == e->clients)
            e->clients = client->next;
        client->next = NULL;
        client->prev = NULL;
        ft_memdel((void **)&client->buffer);
        ft_cbuf_free(client->cbuf);
        ft_memdel((void **)&client);
        e->client_count--;
        FD_CLR(fd, &e->clients_fd_set);
        close(fd);
    }
}