#include "../inc/private_irc.h"
//this function does not work.
static int check_nl(t_client *client){
    t_cbuf  tmp_cbuf;
    uint8_t data;
    int  count;
    
    tmp_cbuf = client->cbuf;
    count = -1;
    while((ft_cbuf_get(tmp_cbuf, &data)) == 0){
        if (data == '\n')
            return (++count);
        ++count;
    }
    return(count);
}

static char *get_cmd(t_client *client, char *cmd){
    int len;
    int count;

    uint8_t data;
    if ((len = check_nl(client)) != -1){
        ft_printf("%d", len);
        ft_strclr(cmd);
        count = 0;
        while (ft_cbuf_get(client->cbuf, &data) == 0 && count < len){
            ft_printf("%s\n", cmd);
            cmd[count++] = data;
        }
    }
    return (cmd);
}

void s_msg_send(t_env *e, int sender_fd){
    t_client    *client;
    int         count;
    char        buffer[MSG_BUFFER_SIZE];
    char        cmd[MSG_SIZE + 1];
    char        *tmp = buffer;

    
    if(!(client = s_find_client(e, sender_fd)))
        return ;
    ft_strclr(buffer);
    tmp = ft_strcat(tmp, client->nick);
    tmp = ft_strcat(tmp, MSG_SEPERATOR);
    tmp = ft_strcat(tmp, get_cmd(client, cmd));
    // count = ft_strlen(tmp);
    // tmp[count] = '\0';
    ft_printf("%s\n", tmp);
    for (int j = 0; j<=e->fd_max; j++){
        if (s_find_client(e, j))
            if (j != sender_fd)
                ft_sendall(j, (uint8_t *) tmp, &count, 0);
    }
}