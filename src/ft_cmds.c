#include "../inc/private_irc.h"
int     s_channel_ismember(t_client *client, int channel){

    if (client->channel == channel)
        return (1);
    return(0);
}

t_client *s_find_nick(t_env *e, char *nick){
    t_client *run;

    if (!e || !nick)
        return (NULL);
    run = e->clients;
    while (run){
        if (ft_strequ(run->nick, nick))
            return run;
        run = run->next;
    }
    return NULL;
}

void cmd_msg(t_env *e, t_client *client, char *nick, char *msg){
    t_client    *receiver;
    int         len;
    
    assert(e && client && nick && msg);
    if ((!ft_strlen(nick) > 0) && !(ft_strlen(msg) > 0))
        return ;
    len = ft_strlen(msg);
    if ((ft_strlen(nick) > 0) && (receiver = s_find_nick(e, nick))){ // send to specific nick
        ft_sendall(receiver->fd, msg, &len, 0);
    } else {    //send to all channel members
        receiver = e->clients;
        while (receiver){
            if(s_channel_ismember(receiver, client->channel) && receiver != client)
                ft_sendall(receiver->fd, msg, &len, 0);
            receiver = receiver->next;
        }
    }
}

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
            msg = ft_strjoin(msg, client->nick);
            ft_strdel(&tmp);
        }
        run = run->next;
    }
    if ((len = ft_strlen(msg)) > 0)
        ft_sendall(client->fd, (uint8_t *) msg, &len, 0);
}