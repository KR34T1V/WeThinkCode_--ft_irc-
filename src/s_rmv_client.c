#include "../inc/private_irc_server.h"

static void pick_out_client(t_env_s *e, t_client *client){
    if (client->next)
        client->next->prev = client->prev;
    if (client->prev)
        client->prev->next = client->next;
    if (client == e->clients)
        e->clients = client->next;
    client->next = NULL;
    client->prev = NULL;
}

void s_rmv_client(t_env_s *e, int fd){
    t_client *client;

    if((client = s_find_client(e, fd))){
        ft_printf("IRC Server: %s on %s disconnected from socket %d\n",client->nick, client->ip_address, client->fd);
        pick_out_client(e, client);
        if (e->clients && client->fd == e->fd_max)
            e->fd_max = e->clients->fd;
        ft_memdel((void **)&client->buffer);
        ft_cbuf_free(client->cbuf);
        ft_memdel((void **)&client);
        e->client_count--;
        FD_CLR(fd, &e->clients_fd_set);
        close(fd);
    }
}