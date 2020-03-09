#include "../inc/private_irc.h"

void client_readstreamdata(int fd){
    char buf[BUFF_SIZE];
    ft_printf("Waiting on data package.\n");
    recv(fd, buf, sizeof(buf),0);
    ft_printf("read: %d\nbuf: %s\n", fd, buf);
}