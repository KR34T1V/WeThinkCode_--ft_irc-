#include "../inc/private_irc.h"
static void max_clients(t_env_s *e, t_client *client){
	if (e->client_count > MAX_CLIENTS){
		ft_printf("IRC Server: Server Full! %d/%d clients online.\n", MAX_CLIENTS, MAX_CLIENTS);
		s_status_send(client, "Server full, please try again later.\n");
		s_rmv_client(e, client->fd);
	}
}

/*
	Creates a new client element in the environment "e", Initialising the Client.
*/
static void new_client(t_env_s *e, int fd, const char *IP){
	t_client 	*client;
	t_client 	*runner;

	assert(e && fd);
	assert((client = (t_client *)ft_memalloc(sizeof(t_client))));
	assert((client->buffer = (char *)ft_memalloc(sizeof(uint8_t) * MSG_BUFFER_SIZE + 1)));
	client->fd = fd;
	ft_strcpy(client->nick, "ANON");
	ft_memset(client->cmd, '\0', MSG_SIZE + 1);
	client->next = NULL;
	client->cbuf = ft_cbuf_init((uint8_t *)client->buffer, MSG_BUFFER_SIZE + 1);
	ft_memcpy(client->ip_address, IP, INET6_ADDRSTRLEN);
	e->client_count++;
	if (e->clients != NULL){
		runner = e->clients;
		while(runner && runner->next != NULL)
			runner = runner->next;
		runner->next = client;
		client->prev = runner;
	} else {
		client->prev = NULL;
		e->clients = client;
	}
	max_clients(e, client);
}

/*
	attempts to accept a new connection from the "listener", if successfull 
	it will add the new connection to the "clients" set and if needed
	ammend the "fdmax" to the largest fd size.
*/
void s_newclient(t_env_s *e){
	int						newfd;
	const char				*IP;
	char					remoteIP[INET6_ADDRSTRLEN];
	struct sockaddr_storage remoteaddr;
	socklen_t				addrlen;
	
	addrlen = sizeof remoteaddr;
	newfd = accept(e->listener, (struct sockaddr *)&remoteaddr, &addrlen);
	IP = inet_ntop(remoteaddr.ss_family, ft_getaddr_IP((struct sockaddr *)&remoteaddr),
	remoteIP,INET6_ADDRSTRLEN);
	if (newfd == -1){
		perror("accept");
		ft_printf("IRC Server: cannot accept new client from %s on socket %d\n", IP, newfd);
	}
	ft_printf("IRC Server: new connection from %s on socket %d\n", IP, newfd);
	FD_SET(newfd, &e->clients_fd_set);	//add to clients
	new_client(e, newfd, IP);
	if (newfd > e->fd_max)
		e->fd_max = newfd;
}