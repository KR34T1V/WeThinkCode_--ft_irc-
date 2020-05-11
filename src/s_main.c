#include "../inc/private_irc.h"

/*
	IRC Server main
*/

int     main(int ac, char** av){
	char	*port;
	t_env	e;
	fd_set	clients;             //client fd list
	fd_set	read_fds;            //temp fd for select
	int		i;

	if (ac < 3 || !s_assign_protocol(&e, av[2])){
		ft_printf("Usage: ./server [port] [local/ipv4/ipv6] \n");
		return(0);
	}
	port = av[1];
	ft_printf("Preparing port: %s\nProtocol: %s\n", port, av[2]);
	FD_ZERO(&clients);			//clear clients
	FD_ZERO(&read_fds);			//clear read_fds
	e.clients = NULL;
	e.listener = s_bindsocket(&e, port);
	s_listen(e.listener, &clients);
	//keep track of biggest file descriptor
	e.fd_max = e.listener;

	//main loop
	ft_printf("Listening...\n");
	while (1){
		read_fds = clients; //current clients
		if (select(e.fd_max + 1, &read_fds, NULL, NULL, NULL) == -1){
			perror("select");
			exit(5);
		}
		//check existing connections
		i = 0;
		while (i <= e.fd_max){
			if (FD_ISSET(i, &read_fds)){
				//new connection
				if (i == e.listener){
					s_newclient(&e, &clients);
				} else {
					s_recvdata(&e, i, &clients);
    				ft_read_cmd(&e, i);
				}
				sleep(5);
			}
			i++;
		}	//Clients loop
	}	//Endless Loop
	return (0);
}