#include "../inc/private_irc.h"

int main(int ac, char **av){
    int fd;

    if (ac < 2){
        ft_printf("Usage: %s (port)\n", av[0]);
        return (0);
    }
    server_launchmessage(av[1]);
    fd = server_bindaddr(av[1]);
    if (fd == -1)
        return(0);
    server_readdatagram(fd);
    return (0);
}