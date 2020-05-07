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
    ft_sendall(client->fd, tmp, &len, 0);
    ft_strdel(&tmp);
}

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
    if ((len = ft_strlen(msg)) > 0){
        s_status_send(client, msg);
        ft_strdel(&msg);
    }
}

void cmd_nick(t_env *e, t_client *client, char *nick){
    assert(e && client && nick);
    if (!(ft_strlen(nick) > 0))
        s_status_send(client, "Nick too short, please try another.");
    if (s_find_nick(e, nick) || ft_strequ(nick, SERVER_NAME)){
        s_status_send(client, "Nick already in use, please try another.");
    } else if (ft_strlen(nick) > NICK_LENGTH) {
        s_status_send(client, "Nick too long, please try another.");
    }
    else {
        ft_strcpy(client->nick, nick);
        s_status_send(client, "Nick successfully changed.");
    }
}

void cmd_join(t_client *client, char *msg){
    assert(client);
    if (ft_strlen(msg) > 0){
        client->channel = ft_atoi(msg);
        s_status_send(client, "Channel changed");
    }
    s_status_send(client, "Channel change failed, please try again.");
}