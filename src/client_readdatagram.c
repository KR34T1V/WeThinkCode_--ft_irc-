#include "../inc/private_irc.h"

void client_readdatagram(int ac, char **av, int fd){
    int i;
    int len;
    long nread;
    char buf[BUFF_SIZE];

    i = 3;
    while (i < ac){
        len = ft_strlen(av[i]) + 1;    
        if (len + 1 > BUFF_SIZE){
            ft_printf("Ignoring long message in argument %d\n", i++);
            continue;
        }
        if (write(fd, av[i], len) != len) {
            ft_printf("partial/failed write\n");
        i++;
        }
        nread = read(fd, buf, BUFF_SIZE);
        if (nread == -1)
            ft_printf("Unable to read incoming trafic");
        ft_printf("Received %zd bytes: %s\n", nread, buf);
    }
}