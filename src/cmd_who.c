#include "../inc/private_irc_server.h"

void cmd_who(t_env_s *e, t_client *client){
    t_client    *run;
    char        *msg;
    char        *tmp;

    assert(e && client);
    run = e->clients;
    msg = ft_strnew(1);
    while (run){
        if (run->channel == client->channel){
            if (ft_strlen(msg) < 1){
                msg = ft_strjoin(msg, run->nick);
            }
            tmp = msg;
            msg = ft_strjoin(msg, ", ");
            ft_strdel(&tmp);
            tmp = msg;
            msg = ft_strjoin(msg, run->nick);
            ft_strdel(&tmp);
        }
        run = run->next;
    }
    if ((ft_strlen(msg)) > 0){
        tmp = msg;
        msg = ft_strjoin(msg, "\n");
        ft_strdel(&tmp);
        s_status_send(client, msg);
        ft_strdel(&msg);
    }
}