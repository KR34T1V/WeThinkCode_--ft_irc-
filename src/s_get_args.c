#include "../inc/private_irc.h"

void s_get_args(char *msg){
    char **args;
    int  len;
    len = ft_wordcount_white(msg);
    ft_printf("%d\n",len);
    args = ft_strsplit_white(msg);
    if (args[0][0] == ':')
        ft_printf("PREFIX");
    for(int i = 0; args[i] != NULL; i++)
            ft_printf("%s\n", args[i]);
}
