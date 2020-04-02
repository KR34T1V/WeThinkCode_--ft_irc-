#include "../inc/private_irc.h"

int c_bind(const char *address, const char *port, struct addrinfo *server_info){
	int val;
	int socket_fd;
	char s[INET6_ADDRSTRLEN];
	struct addrinfo hints;
	struct addrinfo *p;

    //Bind a socket
	ft_memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;				// ipv4 AF_INET | ipv6 AF_INET6
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	if ((val = getaddrinfo(address, port, &hints, &server_info)) != 0){
		ft_printf("IRC Client: %s\n", gai_strerror(val));
		exit(1);
	}
	p = server_info;
	while (p != NULL){
		socket_fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
		if (socket_fd < 0){
			p = p->ai_next;
			continue;
		}
		//remove address already in use error
		val = 1;
		setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(int));
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
    inet_ntop(p->ai_family, ft_getaddr_IP((struct sockaddr *)p->ai_addr),
	s, sizeof(s));
	ft_printf("IRC Client: new connection to %s on socket %d\n", s, socket_fd);
    return (socket_fd);
}