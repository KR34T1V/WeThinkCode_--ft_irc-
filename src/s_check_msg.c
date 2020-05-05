#include "../inc/private_irc.h"

bool    s_checkmsg(t_client *client){
    uint8_t *buffer;
    if (!client)
            return(0);
    while(buffer)
    ft_cbuf_get(client->cbuf, buffer);
    ft_printf("%s", buffer);
    return (1);
}