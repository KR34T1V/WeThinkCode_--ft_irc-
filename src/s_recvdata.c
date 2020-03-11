#include "../inc/private_irc.h"

void	s_recvdata(int fd, fd_set *clients, char *buf){
	int nbytes;

	//client existst and sent data
	if ((nbytes = recv(fd, buf, sizeof(buf), 0)) <= 0){
		//error or client closed connection.
		if (nbytes == 0){
			//connection closed
			ft_printf("IRC Server: socket %d disconnected\n", fd);
		} else {
			perror("recv");
		}
		close(fd);
		FD_CLR(fd,clients); //remove from clients
	} else {
		//data received from client
		ft_printf("%d bytes: %s\n", nbytes, buf);
	}
}