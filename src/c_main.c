#include "../inc/private_irc_client.h"

int main(void){
	char 			*address = "127.0.0.1";
	char 			*port = "1025";
	int 			socket_fd;
	int 			numbytes;
	char 			buf[MSG_SIZE +1];
	struct addrinfo hints;
	struct addrinfo *server_info;
	struct addrinfo *p;
	int 			val;
	char 			s[INET6_ADDRSTRLEN];

	//Bind a socket
	ft_memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
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
	ft_printf("IRC Client: new connection to %s:%s on socket %d\n", s, port, socket_fd);
	freeaddrinfo(server_info);
	//main loop
	while (1){
		c_getinput(socket_fd);
		if ((numbytes = recv(socket_fd, buf, (MSG_BUFFER_SIZE - 1), 0)) == -1){
			perror("recv");
			exit(1);
		}
		if (numbytes == 0){
			ft_printf("IRC Client: Host closed connection.\n");
			break;
		} else {
			buf[numbytes]= '\0';
			ft_printf("%s", buf);
		}
	}
	close(socket_fd);
	return (0);
}