#include "../inc/private_irc.h"
int s_check_nick(t_list *elem, char nick){
    t_client *tmp;

    tmp = (t_client *) elem;
    if (ft_strnequ(nick, tmp->nick, NICK_LENGTH))
        return (1);
    return (0);
}

void s_cmd_nick(t_list *elem, char *nick){
    if (elem == NULL || !nick){
        ft_printf("server error on nick");
        return ;
    }
}