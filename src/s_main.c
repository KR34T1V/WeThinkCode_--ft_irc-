#include "../inc/private_irc.h"

/*
	IRC Server main
*/

int     main(){
	char *port = "1025"; 

	t_env	e;

	fd_set clients;             //client fd list
	fd_set read_fds;            //temp fd for select
	int i;

	FD_ZERO(&clients);			//clear clients
	FD_ZERO(&read_fds);			//clear read_fds

	e.clients = NULL;
	e.listener = s_bindsocket(port);
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
					//get_next_line
					s_msg_send(&e, i);
				}
			}
			i++;
		}	//Clients loop
	}	//Endless Loop
	return (0);
}