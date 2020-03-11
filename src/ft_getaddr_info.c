#include "../inc/private_irc.h"

/*
	Finds wether the connection is IPv4 or IPv6
*/

void *ft_getaddr_info(struct sockaddr *sa){
	if(sa->sa_family == AF_INET)
		return (&(((struct sockaddr_in*)sa)->sin_addr));
	return(&(((struct sockaddr_in6*)sa)->sin6_addr));
}