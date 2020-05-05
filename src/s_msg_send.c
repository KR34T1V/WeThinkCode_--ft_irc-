#include "../inc/private_irc.h"

void s_msg_send(t_env *e, int sender_fd){
    t_client    *client;
    uint8_t     data;
    int         count;
    char        buffer[MSG_BUFFER_SIZE];
    
    if(!(client = s_find_client(e, sender_fd)))
        return ;
    count = 0;
    while((ft_cbuf_get(client->cbuf, &data)) == 0){
        buffer[count++] = (char) data;
    }
    buffer[count] = '\0';
    for (int j = 0; j<=e->fd_max; j++){
        if (s_find_client(e, j))
            if (j != sender_fd)
                ft_sendall(j, (uint8_t *) buffer, &count, 0);
    }
}