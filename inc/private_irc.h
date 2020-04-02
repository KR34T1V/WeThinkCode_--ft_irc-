#ifndef PRIVATE_IRC_H
#define PRIVATE_IRC_H

#define _POSIX_C_SOURCE 200112L
#define NI_MAXHOST 1025
#define NI_MAXSERV 32
#define BUFFER 500

#define LOCAL AF_INET
#define IPV4 AF_INET
#define IPV6 AF_INET6

//Includes
#include "../lib/printf/inc/export_ft_printf.h"
#include <sys/types.h>
#include <stdlib.h> 
#include <sys/socket.h>
#include <errno.h>
#include <netdb.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include <arpa/inet.h>


//Declarations

#include "./constants.h"

//GENERAL
void 				*ft_getaddr_IP(struct sockaddr *sa);
int                 ft_sendall(int fd, char *buf, int *len, int flags);

//SERVER
int 				s_bindsocket(const char *port);
void				s_listen(int listener, fd_set *clients);
void 				s_newclient(int listener, int *fdmax, fd_set *clients);
void				s_recvdata(int fd, fd_set *clients, char *buf);

//CLIENT

#endif