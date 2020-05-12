#include "../inc/private_irc_server.h"

int     s_channel_ismember(t_client *client, int channel){

    if (client->channel == channel)
        return (1);
    return(0);
}