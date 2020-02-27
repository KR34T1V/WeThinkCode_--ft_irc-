#include "../inc/private_irc.h"

struct addrinfo* client_getaddrinfo(char *host, char *port){
    struct addrinfo hints;
    struct addrinfo *result;
    int val;

    ft_memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_protocol = 0;
    hints.ai_flags = 0;

    val = getaddrinfo(host, port, &hints, &result);
    if (val != 0){
        ft_printf("getaddrinfo: %s\n", gai_strerror(val));
        return (NULL);
    }
    else return (result);
}