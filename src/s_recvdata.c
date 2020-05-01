#include "../inc/private_irc.h"

int	s_recvdata(t_env *e ,int fd, fd_set *clients){
	t_client *client;
	int nbytes;

	client = s_find_client(e, fd);
	//client exists and sent data
	if ((nbytes = recv(fd, client->buffer, MSG_SIZE -2, 0)) <= 0){
		//error or client closed connection.
		if (nbytes == 0){
			//connection closed
			ft_printf("IRC Server: socket %d disconnected\n", fd);
		} else {
			perror("recv");
		}
		close(fd);
		FD_CLR(fd,clients); //remove from clients
		return(0);
	}
	//data received from client
	ft_strcpy(&client->buffer[nbytes - 1],"\n\r\0");
	ft_printf("%d bytes from %d: %s\n", nbytes, fd, client->buffer);
	return (nbytes);
}