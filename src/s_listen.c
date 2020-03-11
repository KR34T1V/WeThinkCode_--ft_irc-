#include "../inc/private_irc.h"

void s_listen(int listener, fd_set *clients){
	//listen
	if (listen(listener, LISTEN_BACKLOG) == -1){
		perror("Listen");
		exit(3);
	}
	//add listener to clients
	FD_SET(listener, clients);
	if (listener >= FD_SETSIZE){
		ft_printf("fd limit exceeded.\ncurrent fd: %d\nmax fd: %d", listener, FD_SETSIZE);
		perror("fdsize");
		exit (4);
	}
}