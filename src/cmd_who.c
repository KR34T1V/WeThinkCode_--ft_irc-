#include "../inc/private_irc.h"

void cmd_who(t_env *e, t_client *client){
    t_client    *run;
    char        *msg;
    char        *tmp;
    int         len;

    assert(e && client);
    msg = ft_strnew(1);
    run = e->clients;
    while (run){
        if (run->channel == client->channel){
            tmp = msg;
            if (ft_strlen(msg) > 0){
                msg = ft_strjoin(msg, ", ");
                ft_strdel(&tmp);
            }
            msg = ft_strjoin(msg, run->nick);
            ft_strdel(&tmp);
        }
        run = run->next;
    }
    if ((len = ft_strlen(msg)) > 0){
        tmp = ft_strjoin(msg, "\n");
        ft_strdel(&msg);
        s_status_send(client, tmp);
        ft_strdel(&tmp);
    }
}