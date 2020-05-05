#include "../inc/private_irc.h"
/*
	Creates a new client element in the environment "e", Initialising the Client.
*/
static void new_client(t_env *e, int fd){
	t_client 	*client;
	t_client 	*runner;

	assert(e && fd);
	assert((client = (t_client *)ft_memalloc(sizeof(t_client))));
	assert((client->buffer = (char *)ft_memalloc(sizeof(uint8_t) * MSG_BUFFER_SIZE)));
	client->fd = fd;
	ft_strcpy(client->nick, "ANON");
	client->next = NULL;
	client->cbuf = ft_cbuf_init((uint8_t *)client->buffer, MSG_BUFFER_SIZE);
	if (e->clients != NULL){
		runner = e->clients;
		while(runner && runner->next != NULL)
			runner = runner->next;
		runner->next = client;
		// ft_printf("prev %d\ncurrent %d\n",runner->fd, runner->next->fd);
		client->prev = runner;
	} else {
		client->prev = NULL;
		e->clients = client;
	}
}

/*
	attempts to accept a new connection from the "listener", if successfull 
	it will add the new connection to the "clients" set and if needed
	ammend the "fdmax" to the largest fd size.
*/
void s_newclient(t_env *e, fd_set *clients){
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
	FD_SET(newfd, clients);	//add to clients
	new_client(e, newfd);
	if (newfd > e->fd_max)
		e->fd_max = newfd;
	ft_printf("IRC Server: new connection from %s on socket %d\n", IP, newfd);
}