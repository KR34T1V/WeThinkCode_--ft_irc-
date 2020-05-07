#include "../inc/private_irc.h"

void s_status_send(t_client *client, char *msg){
    int len;
    char *tmp;
    char *tmp2;
    
    assert(client && msg);   
    if (!(ft_strlen(msg) > 0))
        return ;
    tmp = ft_strjoin(SERVER_NAME, MSG_SEPERATOR);
    tmp2 = tmp;
    tmp = ft_strjoin(tmp, msg);
    ft_strdel(&tmp2);
    len = ft_strlen(tmp) + 1;
    ft_sendall(client->fd,(uint8_t *) tmp, &len, 0);
    ft_strdel(&tmp);
}