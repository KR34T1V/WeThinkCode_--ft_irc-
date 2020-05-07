#include "../inc/private_irc.h"

void cmd_join(t_client *client, char *msg){
    assert(client);
    if ((ft_strequ(client->nick, ANON_NICK))){
        s_status_send(client, "Please change your NICK first.\n");
        return ;
    }
    if (ft_strlen(msg) > 0 ){
        client->channel = ft_atoi(msg);
        s_status_send(client, "Channel changed.\n");
    }
    s_status_send(client, "Channel change failed, please try again.\n");
}