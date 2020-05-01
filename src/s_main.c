#include "../inc/private_irc.h"

/*
	IRC Server main
*/

int     main(){
	char *port = "1025"; 

	t_env	e;

	fd_set clients;             //client fd list
	fd_set read_fds;            //temp fd for select
	char buf[MSG_SIZE];        //Buffer for Client Data
	int i;
	int buf_len;

	e.t_list = NULL;
	FD_ZERO(&clients);			//clear clients
	FD_ZERO(&read_fds);			//clear read_fds

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
					s_recvdata(i, &clients, buf);
					s_get_args(buf);
					buf_len = ft_strlen(buf);
					for (int j = 0; j<=e.fd_max; j++){
						//ft_printf("checking %d\n", j);
						if (FD_ISSET(j, &clients)){
							//ft_printf("active\n");
							if (j != e.listener && j != i)
								ft_sendall(j, buf, &buf_len, 0);
						}
					}
				}
			}
			i++;
		}	//Clients loop
	}	//Endless Loop
	return (0);
}