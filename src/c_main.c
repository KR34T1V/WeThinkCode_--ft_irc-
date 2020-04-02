#include "../inc/private_irc.h"

int main(void){
	char *address = "127.0.0.1";
	char *port = "1025";
	int socket_fd;
	int numbytes;
	char buf[BUFF_SIZE];
	struct addrinfo *server_info = NULL;
	socket_fd = c_bind(address, port, server_info);
	freeaddrinfo(server_info);
	if ((numbytes = recv(socket_fd, buf, BUFF_SIZE - 1, 0)) == -1){
		perror("recv");
		exit(1);
	}
	buf[numbytes]= '\0';
	ft_printf("client: received '%s'\n", buf);
	close(socket_fd);
	return (0);
}