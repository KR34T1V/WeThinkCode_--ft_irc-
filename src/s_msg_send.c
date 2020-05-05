#include "../inc/private_irc.h"

void s_msg_send(t_env *e, int sender_fd){
    t_client *client;
    uint8_t data;
    uint8_t buffer[MSG_SIZE];
    // char    *msg;
    // char    *tmp;
    int     len;
    // size_t  count;
    
    if(!(client = s_find_client(e, sender_fd)) || !ft_strlen(client->buffer))
        return ;
    // count = 0;
    while(ft_cbuf_get(client->cbuf, &data)){
        ft_printf("%c", data);
    }
    // tmp = ft_strjoin(client->nick, MSG_SEPERATOR);
    // msg = ft_strjoin(tmp, client->buffer);
    // free(tmp);
    // len = ft_strlen(msg) + 1;
    for (int j = 0; j<=e->fd_max; j++){
        if (s_find_client(e, j))
            if (j != sender_fd)
                ft_sendall(j, buffer, &len, 0);
    }
}