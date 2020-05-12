#ifndef PRIVATE_IRC_H
#define PRIVATE_IRC_H

#define _POSIX_C_SOURCE 200112L

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

//GENERAL
void 				*ft_getaddr_IP(struct sockaddr *sa);
int                 ft_sendall(int fd, uint8_t *buf, int *len, int flags);

//CLIENT
void                c_getinput(int fd);


#endif