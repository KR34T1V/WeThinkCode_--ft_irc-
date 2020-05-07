#include "../inc/private_irc.h"

void cmd_msg(t_env *e, t_client *client, char *nick, char *msg){
    t_client    *receiver;
    int         len;
    
    assert(e && client && nick && msg);
    if ((!(ft_strlen(nick) > 0)) && !(ft_strlen(msg) > 0))
        return ;
    len = ft_strlen(msg);
    if ((ft_strlen(nick) > 0) && (receiver = s_find_nick(e, nick))){ // send to specific nick
        ft_sendall(receiver->fd, (uint8_t *)msg, &len, 0);
    } else {    //send to all channel members
        receiver = e->clients;
        while (receiver){
            if(s_channel_ismember(receiver, client->channel) && receiver != client)
                ft_sendall(receiver->fd,(uint8_t *) msg, &len, 0);
            receiver = receiver->next;
        }
    }
}