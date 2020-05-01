#include "../inc/private_irc.h"

static int check_nick(t_env *e, char*nick){
    t_client *runner;

    if (!e || !e->clients)
        return(1);
    runner = e->clients;
    while (runner){
        if (ft_strnequ(nick, runner->nick, NICK_LENGTH))
            return (0);
        runner = runner->next;
    }
    return(1);
}

int cmd_nick(t_env *e,int fd, char *nick){
    t_client *client;
    
    if ((client = s_find_client(e, fd))){
        if (check_nick(e,nick)){
            ft_strncpy(client->nick, nick, NICK_LENGTH);
            ft_printf("nickname = |%s|", client->nick);
            return (1);
        }
    }
    return (0);
}