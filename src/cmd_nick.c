#include "../inc/private_irc.h"

void cmd_nick(t_env *e, t_client *client, char *nick){
    t_client    *run;
    char        *tmp;
    char        *tmp2;

    assert(e && client && nick);
    nick[ft_strlen(nick) - 1] = '\0';
    if (!(ft_strlen(nick) > 0)){
        s_status_send(client, "Nick too short, please try another.\n");
    } else if (s_find_nick(e, nick) || ft_strequ(nick, SERVER_NAME)){
        s_status_send(client, "Nick already in use, please try another.\n");
    } else if (ft_strlen(nick) > NICK_LENGTH) {
        s_status_send(client, "Nick too long, please try another.\n");
    } else {
        run = e->clients;
        tmp2 = tmp;
        tmp = ft_strjoin(client->nick, " changed their nick to ");
        tmp2 = ft_strjoin(tmp, nick);
        ft_strdel(&tmp);
        tmp = ft_strjoin(tmp2, "\n");
        ft_strdel(&tmp2);
        while (run){
            if (run->channel == client->channel && run != client){
                s_status_send(run, tmp);
            }
            run = run->next;
        }
        ft_strdel(&tmp);
        ft_strcpy(client->nick, nick);
        s_status_send(client, "Nick successfully changed.\n");
    }
}