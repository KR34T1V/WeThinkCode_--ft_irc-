#include "../inc/private_irc.h"

void server_readdatagram(int fd){
    char buf[BUFF_SIZE];
    long nread;
    struct sockaddr_storage peer_addr;
    socklen_t peer_addr_len;

    peer_addr_len = sizeof(struct sockaddr_storage);
    while (1 == 1){
        nread = recvfrom(fd, buf, BUFF_SIZE, 0, (struct sockaddr *)&peer_addr, &peer_addr_len);
        if (nread == -1)
            continue;
        int val;
        char host[NI_MAXHOST];
        char service[NI_MAXSERV];

        val = getnameinfo((struct sockaddr *) &peer_addr, peer_addr_len, host, NI_MAXHOST, service, NI_MAXSERV, NI_NUMERICSERV);
         if (val == 0)
            ft_printf("Received %zd bytes from %s:%s\n", nread, host, service);
        else
            ft_printf("getnameinfo: %s\n", gai_strerror(val));
        if (sendto(fd, buf, nread, 0,(struct sockaddr *) &peer_addr, peer_addr_len) != nread)
                   ft_printf("Error sending response\n");

    }

}