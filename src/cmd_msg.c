#include "../inc/private_irc.h"

void cmd_msg(t_env *e, t_client *client, char *nick, char *msg){
    t_client    *receiver;
    int         len;
    char        *tmp;
    char        *tmp2;
    
    assert(e && client && nick && msg);
    if ((ft_strequ(client->nick, ANON_NICK))){
        s_status_send(client, "Please change your NICK first.\n");
        return ;
    }
    tmp = ft_strjoin(client->nick, MSG_SEPERATOR);
    tmp2 = tmp;
    if (ft_strequ(nick, ANON_NICK))
        return ;
    if ((receiver = s_find_nick(e, nick))){
        msg = ft_strtrim(msg + ft_strlen(nick));
        tmp = ft_strjoin(tmp, msg);
        ft_strdel(&msg);
    }   else {
        tmp = ft_strjoin(tmp, msg);
    }
    ft_strdel(&tmp2);
    if ((!(ft_strlen(nick) > 0)) || !(ft_strlen(tmp) > 0))
        return ;
    len = ft_strlen(tmp);
    if (receiver){ // send to specific nick
        ft_sendall(receiver->fd, (uint8_t *)tmp, &len, 0);
    } else {    //send to all channel members
        receiver = e->clients;
        while (receiver){
            if(s_channel_ismember(receiver, client->channel) && receiver != client)
                ft_sendall(receiver->fd, (uint8_t *)tmp, &len, 0);
            receiver = receiver->next;
        }
    }
}