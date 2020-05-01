#include "../inc/private_irc.h"

static void new_client(t_env *e, int fd){
	t_client	c;
	t_client	*client;
	
	client = (t_client *)ft_lstnew(&c, sizeof(t_client));
	client->fd = fd;
	
	if (e->t_list == NULL){
		e->t_list = client;
	} else{
		ft_lstadd(e->t_list, (t_list *)client);
	}
}

/*
	attempts to accept a new connection from the "listener", if successfull 
	it will add the new connection to the "clients" set and if needed
	ammend the "fdmax" to the largest fd size.
*/
void s_newclient(t_env *e, fd_set *clients){
	int						newfd;
	char					remoteIP[INET6_ADDRSTRLEN];
	struct sockaddr_storage remoteaddr;
	socklen_t				addrlen;
	

	addrlen = sizeof remoteaddr;
	newfd = accept(e->listener, (struct sockaddr *)&remoteaddr, &addrlen);
	if (newfd == -1){
		perror("accept");
		ft_printf("IRC Server: cannot accept new client from %s on socket %d\n", inet_ntop(remoteaddr.ss_family, ft_getaddr_IP((struct sockaddr *)&remoteaddr), remoteIP,INET6_ADDRSTRLEN), newfd);
	}
	FD_SET(newfd, clients);	//add to clients
	new_client(e, newfd);
	if (newfd > e->fd_max)
		e->fd_max = newfd;
	ft_printf("IRC Server: new connection from %s on socket %d\n", inet_ntop(remoteaddr.ss_family, ft_getaddr_IP((struct sockaddr *)&remoteaddr), remoteIP,INET6_ADDRSTRLEN), newfd);
}