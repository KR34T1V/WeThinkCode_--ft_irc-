#include "../inc/private_irc.h"

struct addrinfo* server_getaddrinfo(char *port){
    struct addrinfo hints;
    struct addrinfo *result;
    int val;

    ft_memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = AF_UNSPEC;
    hints.ai_protocol = 0;
    hints.ai_flags = AI_PASSIVE;
    hints.ai_canonname = NULL;
    hints.ai_addr = NULL;
    hints.ai_next = NULL;

    val = getaddrinfo(NULL, port, &hints, &result);
    if (val != 0){
        ft_printf("getaddrinfo: %s\n", gai_strerror(val));
        return (NULL);
    }
    else return (result);
}