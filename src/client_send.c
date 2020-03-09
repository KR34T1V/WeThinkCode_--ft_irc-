#include "../inc/private_irc.h"

void    client_send(int fd, char *message){
    int len;
    len = sizeof(message);
    if (write(fd, (void *)message, len) != len)
        ft_printf("!!!partial/failed write!!!\nRetrying...\n");
}