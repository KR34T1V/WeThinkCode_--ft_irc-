#include "../inc/private_irc_client.h"

void c_getinput(int fd){
    int len;
    char input[MSG_SIZE +1];
    char *tmp;
    
    if((len = read(STDIN_FILENO, input, MSG_SIZE)) < 0){
        ft_printf("IRC Client: Read Error!\n");
        return ;
    }
    input[len] = '\0';
    if ((tmp = ft_strchr(input, '\n'))){
        *++tmp = '\0';
    } else {
        return ;
    }
    len = ft_strlen(input);
    ft_sendall(fd, (uint8_t *)input, &len, 0);
    ft_strclr(input);
}