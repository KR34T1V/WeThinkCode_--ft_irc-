#include "../inc/private_irc.h"

static void s_args_check(char *cmd){
    char *tmp;
    tmp = ft_strtoupper(cmd);
    if (ft_strequ(tmp, "PASS"))
        ft_printf("%s", "PASS");

    if (ft_strequ(tmp,"NICK"))
        ft_printf("%s", "NICK");
}

void s_get_args(char *msg){
    char **args;
    int  len;
    len = ft_wordcount_white(msg);
    args = ft_strsplit_white(msg);
    ft_printf("%d\n",len);
    if (args[0][0] == ':'){
        ft_printf("PREFIX");
    } else {
        s_args_check(args[0]);
    }
    for(int i = 0; args[i] != NULL; i++)
            ft_printf("%s\n", args[i]);
}
