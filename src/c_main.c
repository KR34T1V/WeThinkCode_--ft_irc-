#include "../inc/private_irc_client.h"

int main(int ac, char **av){
	char 			*address;
	char 			*port;
	int 			socket_fd;
	int 			numbytes;
	char 			buf[MSG_SIZE +1];
	t_env_c			e;

	if (ac < 3){
		ft_printf("Usage: ./client [host_address] [port]\n");
		return (0);
	}
	address = av[1];
	port = av[2];
	FD_ZERO(&e.server_fds);
	FD_ZERO(&e.read_fds);
	FD_SET(STDIN_FILENO,&e.server_fds);
	//add a listener here to have more then one server.
	socket_fd = c_bind(address, port);
	c_connection_new(&e, socket_fd,address);
	while (1){
		c_select_fd(&e);
		if (FD_ISSET(STDIN_FILENO, &e.read_fds))
			c_getinput(socket_fd);
		if (FD_ISSET(socket_fd, &e.read_fds)){
			if ((numbytes = recv(socket_fd, buf, (MSG_BUFFER_SIZE - 1), 0)) == -1){
				c_connection_rmv(&e, socket_fd);
				perror("recv");
				break;
			}
			if (numbytes == 0){
				ft_printf("IRC Client: Host closed connection.\n");
				c_connection_rmv(&e, socket_fd);
				break;
			} else {
				buf[numbytes]= '\0';
				ft_printf("%s", buf);
			}
		}
	}
	close(socket_fd);
	return (0);
}