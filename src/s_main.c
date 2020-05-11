#include "../inc/private_irc.h"

static void run(t_env *e, fd_set *read_fds){
	int		i;

	i = 0;
	while (i <= e->fd_max){
		if (FD_ISSET(i, read_fds)){
			//new connection
			if (i == e->listener){
				s_newclient(e);
			} else {
				s_recvdata(e, i);
				ft_read_cmd(e, i);
			}
		}
		i++;
	}	//Clients loop
}

int     main(int ac, char** av){
	char	*port;
	t_env	e;
	fd_set	read_fds;            //temp fd for select
	struct timeval timeout;

	if (ac < 3 || !s_assign_protocol(&e, av[2])){
		ft_printf("Usage: ./server [port] [local/ipv4/ipv6] \n");
		return(0);
	}
	port = av[1];
	ft_printf("Preparing port: %s\nProtocol: %s\n", port, av[2]);
	FD_ZERO(&e.clients_fd_set);			//clear clients
	FD_ZERO(&read_fds);			//clear read_fds
	e.clients = NULL;
	e.client_count = 0;
	e.listener = s_bindsocket(&e, port);
	s_listen(e.listener, &e.clients_fd_set);
	//keep track of biggest file descriptor
	e.fd_max = e.listener;

	//main loop
	ft_printf("Listening...\n");
	while (1){
		timeout.tv_sec = LISTEN_TIMEOUT;
		read_fds = e.clients_fd_set; //current clients
		if (select(e.fd_max + 1, &read_fds, NULL, NULL, &timeout) == -1){
			perror("select");
			exit(5);
		}
		//check existing connections
		run(&e, &read_fds);
	}	//Endless Loop
	return (0);
}