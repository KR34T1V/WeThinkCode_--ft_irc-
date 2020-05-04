#ifndef PRIVATE_IRC_H
#define PRIVATE_IRC_H

#define _POSIX_C_SOURCE 200112L
#define NI_MAXHOST 1025
#define NI_MAXSERV 32

#define LOCAL AF_INET
#define IPV4 AF_INET
#define IPV6 AF_INET6

//Includes
#include "../lib/printf/inc/export_ft_printf.h"
#include "./export_cbuf.h"
#include <sys/types.h>
#include <stdlib.h> 
#include <sys/socket.h>
#include <errno.h>
#include <netdb.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <assert.h>


//Declarations

#include "./constants.h"

//DATA STRUCTURES
typedef struct          s_client {
    int                 fd;
    char                ip_address[INET6_ADDRSTRLEN];
    char                nick[NICK_LENGTH + 1];
    t_cbuf              buffer;
    int                 *channels;
    struct s_client     *next;
    struct s_client     *prev;
}                       t_client;

typedef struct      s_env   {
    int             listener;
    int             fd_max;
    t_client        *clients;
}                   t_env;

//GENERAL
void 				*ft_getaddr_IP(struct sockaddr *sa);
int                 ft_sendall(int fd, char *buf, int *len, int flags);

//SERVER
int 				s_bindsocket(const char *port);
void				s_listen(int listener, fd_set *clients);
void                s_newclient(t_env *e, fd_set *clients);
int 				s_recvdata(t_env *e, int fd, fd_set *clients);
void                s_get_args(t_env *e, int fd);
t_client            *s_find_client(t_env *e, int fd);
int                 cmd_nick(t_env *e,int fd, char *nick);
void                s_msg_send(t_env *e, int sender_fd);
void                s_rmv_client(t_env *e, int fd);

//CLIENT
void                c_getinput(int fd);


#endif