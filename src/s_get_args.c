#include "../inc/private_irc.h"

/*
    Checks for valid commands. 
*/
void s_get_args(char *msg){
    char **args;
    char *tmp;
    
    args = ft_strsplit_white(msg);
    if (args[0][0] == ':'){
        ft_printf("Prefix ignored for now.");
    } else {
        tmp = ft_strtoupper(args[0]);
        if (ft_strequ(tmp, "PASS"))
            ft_printf("%s", "PASS\n");
        if (ft_strequ(tmp,"NICK"))
            ft_printf("%s", "NICK\n");
        if (ft_strequ(tmp,"QUIT"))
            ft_printf("%s", "QUIT\n");
        if (ft_strequ(tmp,"JOIN"))
            ft_printf("%s", "JOIN\n");
        if (ft_strequ(tmp,"LEAVE"))
            ft_printf("%s", "LEAVE\n");
        if (ft_strequ(tmp,"WHO"))
            ft_printf("%s", "WHO\n");
        if (ft_strequ(tmp,"MSG"))
            ft_printf("%s", "MSG\n");
        if (ft_strequ(tmp,"CONNECT"))
            ft_printf("%s", "CONNECT\n");
    }
}
