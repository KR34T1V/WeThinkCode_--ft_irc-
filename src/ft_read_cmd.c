#include "../inc/private_irc.h"
#include <string.h>
static void check_commands(t_env *e, t_client *client){
    char    **args;
    char    *cmd;
    int     i;

    ft_printf("checking commands!\n");
    args = ft_strsplit_white(client->cmd);
    if (args && args[0]){
        cmd = ft_strtoupper(args[0]);
        if (ft_strequ(cmd, CMD_MSG)){
            ft_printf("msg command");
            s_msg_send(e, client);
        }
    }
    i = 1;
    while (args && args[i]){
        ft_printf("%s\n", args[i++]);
    }
    ft_strclr(client->cmd);
}

static void read_buf(t_client *client){
    int count;

    uint8_t data;
    count = ft_strlen(client->cmd);
    while (ft_cbuf_get(client->cbuf, &data) == 0 && count <= MSG_SIZE){
        client->cmd[count++] = data;
        if (data == '\n')
            break;
    }
    client->cmd[count] = '\0';
}

void    ft_read_cmd(t_env *e, int fd){
    t_client *client;

    if(!(client = s_find_client(e, fd)))
        return ;
    read_buf(client);
    ft_printf("cmd: %s\n", client->cmd);
    if(ft_strrchr(client->cmd, '\n'))
        check_commands(e, client);
}