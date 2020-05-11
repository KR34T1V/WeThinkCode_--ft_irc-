#include "../inc/private_irc.h"

int s_bindsocket(t_env *e, const char *port){
	int val;
	int listener;
	struct addrinfo hints;
	struct addrinfo *ai;
	struct addrinfo *p;

	//Bind a socket
	ft_memset(&hints, 0, sizeof(hints));
	hints.ai_family = e->connection_type;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	if ((val = getaddrinfo(NULL, port, &hints, &ai)) != 0){
		ft_printf("IRC Server: %s\n", gai_strerror(val));
		exit(1);
	}
	p = ai;
	while (p != NULL){
		listener = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
		if (listener < 0){
			p = p->ai_next;
			continue;
		}
		//remove address already in use error
		val = 1;
		setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(int));
		if (bind(listener, p->ai_addr, p->ai_addrlen) < 0){
			close(listener);
			p = p->ai_next;
			continue;
		} else {
			break;
		}
		p = p->ai_next;
	}
	if (p == NULL){
		ft_printf("IRC Server: failed to bind\n");
		exit(1);
	}
	freeaddrinfo(ai);
	return (listener);
}