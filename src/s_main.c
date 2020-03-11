#include "../inc/private_irc.h"

/*
	IRC Server main
*/

int     main(){
	char *port = "1025"; 

	fd_set clients;             //client fd list
	fd_set read_fds;            //temp fd for select
	int fdmax;					//maximum fd number
	int newfd;					//new client fd
	int listener;				//listening fd
	char buf[BUFF_SIZE];        //Buffer for Client Data
	int nbytes;
	struct sockaddr_storage remoteaddr;         // Client Address
	socklen_t addrlen;
	char    remoteIP[INET6_ADDRSTRLEN];         //Remote IP Address 
	int yes = 1;
	int i;
	int j;
	int rv;
	struct addrinfo hints;
	struct addrinfo *ai;
	struct addrinfo *p;

	FD_ZERO(&clients);			//clear clients
	FD_ZERO(&read_fds);			//clear read_fds

	//Bind a socket
	ft_memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;				// ipv4 AF_INET | ipv6 AF_INET6
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	if ((rv = getaddrinfo(NULL, port, &hints, &ai)) != 0){
		ft_printf("IRC Server: %s\n", gai_strerror);
		exit(1);
	} 
	p = ai;
	while (p != NULL){
		listener = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
		if (listener < 0){
			p = p->ai_next;
			continue;
		}
		//remove address already in use error
		setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
		if (bind(listener, p->ai_addr, p->ai_addrlen) < 0){
			close(listener);
			p = p->ai_next;
			continue;
		} else {
			break;
		}
		p = p->ai_next;
	}
	if (p == NULL){
		ft_printf("IRC Server: failed to bind\n");
	}
	freeaddrinfo(ai);
	//listen
	if (listen(listener, LISTEN_BACKLOG) == -1){
		perror("Listen");
		exit(3);
	}

	//add listener to clients
	FD_SET(listener, &clients);

	//keep track og biggest file descriptor
	fdmax = listener;
	if (fdmax >= FD_SETSIZE){
		ft_printf("fd limit exceeded.\ncurrent fd: %d\nmax fd: %d", fdmax, FD_SETSIZE);
		perror("fdsize");
	}

	//main loop
	ft_printf("Listening...\n");
	while (1){
		read_fds = clients; //current clients
		if (select(fdmax + 1, &read_fds, NULL, NULL, NULL) == -1){
			perror("select");
			exit(4);
		}
		//check existing connections
		i = 0;
		while (i <= fdmax){
			if (FD_ISSET(i, &read_fds)){
				//new connection
				if (i == listener){
					addrlen = sizeof remoteaddr;
					newfd = accept(listener, (struct sockaddr *)&remoteaddr, &addrlen);
					if (newfd == -1){
						perror("accept");
					} else {
						FD_SET(newfd, &clients);	//add to clients
						if (newfd > fdmax)
							fdmax = newfd;
					}
					ft_printf("IRC Server: new connection from %s on socket %d\n", inet_ntop(remoteaddr.ss_family, ft_getaddr_info((struct sockaddr *)&remoteaddr), remoteIP,INET6_ADDRSTRLEN), newfd);
				} else {
					//client existst and sent data
					if ((nbytes = recv(i, buf, sizeof(buf), 0)) <= 0){
						//error or client closed connection.
						if (nbytes == 0){
							//connection closed
							ft_printf("IRC Server: socket %d disconnected\n", i);
						} else {
							perror("recv");
						}
						close(i);
						FD_CLR(i,&clients); //remove from clients
					} else {
						//data received from client
						ft_printf("IRC Server: data received from socket %d\n", i);
						j = 0;
						while (j <= fdmax){
							//send to everyone
							if (FD_ISSET(j, &clients)){
								//except the listener and ourselves
								if (j != listener && j != i) {
									if (send(j,buf,nbytes,0) == -1){
										perror("send");
									}
								}
							}	//handle data from client
							j++;
						}	
					}	
				}	
			}	//new incoming connection
			i++;
		}	//Clients loop
	}	//Endless Loop
	return (0);
}