#include "../inc/private_irc.h"

int main(int ac, char **av){
    int fd;
    fd_set connections;

    if (ac < 2){
        ft_printf("Usage: %s (port)\n", av[0]);
        return (0);
    }
    fd = server_bindaddr(av[1]);
    if (fd == -1)
        return(0);
    FD_SET(fd, &connections);
    server_launchmessage(av[1]);
    server_connection_listen(fd, &connections);
    // server_readstreamdata(fd);
    //server_readdatagram(fd);
    return (0);
}