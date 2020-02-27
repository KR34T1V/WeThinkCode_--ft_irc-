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

//Declarations

typedef struct s_addrinfo {
               int              ai_flags;
               int              ai_family;
               int              ai_socktype;
               int              ai_protocol;
               socklen_t        ai_addrlen;
               struct sockaddr *ai_addr;
               char            *ai_canonname;
               struct addrinfo *ai_next;
                            } t_addrinfo;
//SERVER
void server_launchmessage(char *port);
struct addrinfo* server_getaddrinfo();
int server_bindaddr(char *port);
void server_readdatagram(int fd);

//CLIENT
void client_launchmessage(char *host, char *port);
struct addrinfo* client_getaddrinfo(char *host, char *port);
int client_connect(char *host, char *port);
void client_readdatagram(int ac, char **av, int fd);

#endif