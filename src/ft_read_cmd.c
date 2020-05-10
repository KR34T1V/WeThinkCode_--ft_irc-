#include "../inc/private_irc.h"
#include <string.h>
static void check_commands(t_env *e, t_client *client){
    char    **args;
    char    *msg;
    char    *cmd;
    args = ft_strsplit_white(client->cmd);
    if (args && args[0]){
        cmd = ft_strtoupper(args[0]);
        if (ft_strequ(cmd, CMD_MSG) && args[1]){
            msg = client->cmd + (ft_strlen(CMD_MSG) + 1);
            cmd_msg(e, client, args[1], msg);
        } else if (ft_strequ(cmd, CMD_NICK)){
            msg = client->cmd + (ft_strlen(CMD_NICK) + 1);
            cmd_nick(e, client, msg);
        } else if (ft_strequ(cmd, CMD_WHO)){
            cmd_who(e, client);
        } else if (ft_strequ(cmd, CMD_JOIN)){
            msg = client->cmd + (ft_strlen(CMD_JOIN) + 1);
            cmd_join(e, client, msg);
        } else {
            s_status_send(client, "Invalid command.\n");
        }
    }
    ft_free2d_char(args);
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
    if(ft_strrchr(client->cmd, '\n'))
        check_commands(e, client);
}