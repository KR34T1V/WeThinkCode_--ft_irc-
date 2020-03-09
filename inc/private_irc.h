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
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>


//Declarations

#include "./constants.h"

//SERVER
int                 server_connection_manage(int fd, int fd_max, fd_set *readfds, fd_set *connections);
int                 server_connection_accept(int fd);
int                 server_connection_listen(int fd, fd_set *connections);
void                server_launchmessage(char *port);
struct addrinfo*    server_getaddrinfo();
int                 server_bindaddr(char *port);

//CLIENT
void                client_launchmessage(char *host, char *port);
struct addrinfo*    client_getaddrinfo(char *host, char *port);
int                 client_connect(char *host, char *port);

#endif