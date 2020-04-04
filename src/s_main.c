#include "../inc/private_irc.h"

/*
	IRC Server main
*/

int     main(){
	char *port = "1025"; 

	fd_set clients;             //client fd list
	fd_set read_fds;            //temp fd for select
	char buf[BUFF_SIZE];        //Buffer for Client Data

	int fdmax;					//maximum fd number
	int listener;				//listening fd


	int i;
	int buf_len;


	FD_ZERO(&clients);			//clear clients
	FD_ZERO(&read_fds);			//clear read_fds

	listener = s_bindsocket(port);
	s_listen(listener, &clients);
	//keep track of biggest file descriptor
	fdmax = listener;

	//main loop
	ft_printf("Listening...\n");
	while (1){
		read_fds = clients; //current clients
		if (select(fdmax + 1, &read_fds, NULL, NULL, NULL) == -1){
			perror("select");
			exit(5);
		}
		//check existing connections
		i = 0;
		while (i <= fdmax){
			if (FD_ISSET(i, &read_fds)){
				//new connection
				if (i == listener){
					s_newclient(listener, &fdmax, &clients);
				} else {
					s_recvdata(i, &clients, buf);
					buf_len = ft_strlen(buf);
					for (int j = 0; j<=fdmax; j++){
						if (FD_ISSET(j, &read_fds))
							ft_sendall(i, buf, &buf_len, 0);
					}
				}
			}
			i++;
		}	//Clients loop
	}	//Endless Loop
	return (0);
}