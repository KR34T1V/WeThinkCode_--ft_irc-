#include "../inc/private_irc.h"

int	s_recvdata(t_env *e ,int fd, fd_set *clients){
	t_client *client;

	uint8_t tmp_buf[MSG_SIZE];
	int nbytes;
	int count;
	if (!(client = s_find_client(e, fd)))
		return 0;
	//client exists and sent data
	if ((nbytes = recv(fd, tmp_buf, MSG_SIZE, 0)) <= 0){
		//error or client closed connection.
		if (nbytes == 0){
			//connection closed
			s_rmv_client(e, fd);
			ft_printf("IRC Server: socket %d disconnected\n", fd);
		} else {
			perror("recv");
		}
		close(fd);
		FD_CLR(fd,clients); //remove from clients
		return(0);
	}
	//data received from client
	count = 0;
	ft_printf("Receiving from: %d\n", fd);
	while (count < nbytes && tmp_buf[count]){
		ft_cbuf_put(client->cbuf, tmp_buf[count++], MSG_BUFFER_OVERWRITE);
	}
	return (nbytes);
}