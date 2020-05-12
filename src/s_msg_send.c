#include "../inc/private_irc.h"

void s_msg_send(t_env_s *e, t_client *client){
    int         count;
    char        buffer[MSG_BUFFER_SIZE];
    char        *tmp = buffer;

    tmp = ft_strcat(tmp, client->nick);
    tmp = ft_strcat(tmp, MSG_SEPERATOR);
    count = ft_strlen(tmp);
    tmp[count] = '\0';
    for (int j = 0; j<=e->fd_max; j++){
        if (s_find_client(e, j))
            if (j != client->fd)
                ft_sendall(j, (uint8_t *) tmp, &count, 0);
    }
}