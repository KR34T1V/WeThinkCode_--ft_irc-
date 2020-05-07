#include "../inc/private_irc.h"
#include <string.h>
static void check_commands(t_client *client){
    char    **args;
    int     i;

    ft_printf("checking commands!\n");
    args = ft_strsplit_white(client->cmd);
    i = 0;
    while (args && args[i]){
        ft_printf("%s\n", args[i++]);
    }
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

void    ft_read_cmd(t_client *client){
    read_buf(client);
    ft_printf("cmd: %s\n", client->cmd);
    if(ft_strrchr(client->cmd, '\n'))
        check_commands(client);
}