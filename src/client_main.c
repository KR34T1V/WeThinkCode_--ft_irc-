#include "../inc/private_irc.h"

int main(int ac, char **av){
    int fd;

    if (ac < 3) {
        ft_printf("Usage: %s (host) (port) (msg...)\n", av[0]);
        return (0);
    }
    client_launchmessage(av[1], av[2]);
    fd = client_connect(av[1],av[2]);
        if (fd == -1)
        return(0);
    client_readdatagram(ac, av, fd);

    return (1);
}