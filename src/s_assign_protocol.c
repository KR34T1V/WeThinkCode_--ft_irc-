#include "../inc/private_irc.h"

int s_assign_protocol(t_env_s *e, const char *protocol){
    char *tmp;

    tmp = ft_strtoupper(protocol);
    if (ft_strequ(tmp, "IPV4")){
        e->connection_type = IPV4;
        return(1);
    } else if (ft_strequ(tmp, "IPV6")){
        e->connection_type = IPV6;
        return(1);
    } else if (ft_strequ(tmp, "LOCAL")){
        e->connection_type = LOCAL;
        return(1);
    }
    return(0);
}