#ifndef PRIVATE_IRC_SERVER_H
#define PRIVATE_IRC_SERVER_H

#include "./private_irc.h"

//DATA STRUCTURES
typedef struct          s_client {
    int                 fd;
    char                ip_address[INET6_ADDRSTRLEN];
    char                nick[NICK_LENGTH + 1];
    char                cmd[MSG_SIZE + 1];
    char                *buffer;
    t_cbuf              cbuf;
    int                 channel;
    struct s_client     *next;
    struct s_client     *prev;
}                       t_client;

typedef struct      s_env_s   {
    int             listener;
    int             fd_max;
    int             connection_type;
    int             client_count;
    fd_set	        clients_fd_set;
    t_client        *clients;
}                   t_env_s;

int 				s_bindsocket(t_env_s *e, const char *port);
int 				s_recvdata(t_env_s *e, int fd);
int                 s_channel_ismember(t_client *client, int channel);
t_client            *s_find_client(t_env_s *e, int fd);
t_client            *s_find_nick(t_env_s *e, char *nick);
void				s_listen(int listener, fd_set *clients);
void                s_newclient(t_env_s *e);
void                s_msg_send(t_env_s *e, t_client *client);
void                s_rmv_client(t_env_s *e, int fd);
void                s_read_cmd(t_env_s *e, int fd);
void                cmd_join(t_env_s *e, t_client *client, char *msg);
void                cmd_msg(t_env_s *e, t_client *client, char *nick, char *msg);
void                cmd_nick(t_env_s *e, t_client *client, char *nick);
void                cmd_who(t_env_s *e, t_client *client);
void                s_status_send(t_client *client, char *msg);
int                 s_assign_protocol(t_env_s *e, const char *protocol);

#endif