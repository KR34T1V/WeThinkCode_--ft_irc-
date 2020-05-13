#include "../inc/private_irc_client.h"

static void pick_out_server(t_env_c *e, t_server_c *server){
    if (server->next)
        server->next->prev = server->prev;
    if (server->prev)
        server->prev->next = server->next;
    if (server == e->servers)
        e->servers = server->next;
    server->next = NULL;
    server->prev = NULL;
}

void c_connection_rmv(t_env_c *e, int fd){
    t_server_c *server;
    assert((server = c_find_server(e, fd)));
    pick_out_server(e, server);
    if (e->servers && server->fd == e->fd_max)
        e->fd_max = e->servers->fd;
    ft_memdel((void *) server);
}