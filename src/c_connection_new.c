#include "../inc/private_irc_client.h"

void c_connection_new(t_env_c *e, int fd, const char *address){
    t_server_c  *server;

    server = ft_memalloc(sizeof(t_server_c));
    assert(e && server);
    server->prev = NULL;
    server->fd = fd;
    if (fd > e->fd_max)
        e->fd_max = fd;
    FD_SET(fd, &e->server_fds);
    ft_memcpy(server->ip_address, address, INET6_ADDRSTRLEN);
    if (!e->servers){
        server->next = NULL;
        e->servers = server;
        return ;
    }
    server->next = e->servers;
    e->servers->prev = server;
    e->servers = server;
}