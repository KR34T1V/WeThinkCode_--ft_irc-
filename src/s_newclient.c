#include "../inc/private_irc.h"

void s_newclient(int listener, int *fdmax, fd_set *clients){
	int newfd;
	char    remoteIP[INET6_ADDRSTRLEN];
	struct sockaddr_storage remoteaddr;
	socklen_t addrlen;
	

	addrlen = sizeof remoteaddr;
	newfd = accept(listener, (struct sockaddr *)&remoteaddr, &addrlen);
	if (newfd == -1){
		perror("accept");
		ft_printf("IRC Server: cannot accept new client from %s on socket %d\n", inet_ntop(remoteaddr.ss_family, ft_getaddr_IP((struct sockaddr *)&remoteaddr), remoteIP,INET6_ADDRSTRLEN), newfd);
	}
	FD_SET(newfd, clients);	//add to clients
	if (newfd > *fdmax)
		*fdmax = newfd;
	ft_printf("IRC Server: new connection from %s on socket %d\n", inet_ntop(remoteaddr.ss_family, ft_getaddr_IP((struct sockaddr *)&remoteaddr), remoteIP,INET6_ADDRSTRLEN), newfd);
}