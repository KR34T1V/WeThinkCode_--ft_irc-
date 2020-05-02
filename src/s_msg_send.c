#include "../inc/private_irc.h"

void s_msg_send(t_env *e, int sender_fd){
    t_client *client;
    char    *msg;
    char    *tmp;
    int     len;
    
    if(!(client = s_find_client(e, sender_fd)))
        return ;
    tmp = ft_strjoin(client->nick, MSG_SEPERATOR);
    msg = ft_strjoin(tmp, client->buffer);
    free(tmp);
    len = ft_strlen(msg) + 1;
    for (int j = 0; j<=e->fd_max; j++){
        if (s_find_client(e, j))
            if (j != sender_fd)
                ft_sendall(j, msg, &len, 0);
    }
}