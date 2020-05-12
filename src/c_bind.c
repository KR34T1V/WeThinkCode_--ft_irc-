#include "../inc/private_irc_client.h"

static struct addrinfo *get_server_info(const char *address, const char *port,
struct addrinfo *server_info){
    struct addrinfo hints;
    int             val;

	ft_memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	if ((val = getaddrinfo(address, port, &hints, &server_info)) != 0){
		ft_printf("IRC Client: %s\n", gai_strerror(val));
		exit(1);
	}
    return (server_info);
}

int c_bind(const char *address, const char *port){
    struct addrinfo *server_info = NULL;
	struct addrinfo *p;
	int 			socket_fd;

    p = get_server_info(address, port, server_info);
	while (p != NULL){
		socket_fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
		if (socket_fd < 0){
			p = p->ai_next;
			continue;
		}
		if (connect(socket_fd, p->ai_addr, p->ai_addrlen) < 0){
			close(socket_fd);
			perror("client: connect");
			p = p->ai_next;
			continue;
		} else {
			break;
		}
		p = p->ai_next;
	}
	if (p == NULL){
		ft_printf("IRC Client: failed to bind\n");
		exit(1);
	}
	freeaddrinfo(server_info);
    return (socket_fd);
}