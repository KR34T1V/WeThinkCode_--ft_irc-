#include "../inc/private_irc.h"

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