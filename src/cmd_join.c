#include "../inc/private_irc.h"

void cmd_join(t_client *client, char *msg){
    assert(client);
    if (ft_strlen(msg) > 0){
        client->channel = ft_atoi(msg);
        s_status_send(client, "Channel changed");
    }
    s_status_send(client, "Channel change failed, please try again.");
}