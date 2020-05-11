#include "../inc/private_irc.h"

void c_getinput(int fd){
    int len;
    char *input;
    char *tmp;
    
    while((len = read(fd, input, MSG_SIZE))){
        if ((tmp = ft_strchr(input, '\n'))){
            tmp = '\0';
            break;
        }
    }
    //invalid input;
    if (len < 1){
        ft_printf("IRC Client: Invalid Input!\n");
        return ;
    }
    len = ft_strlen(input);
    ft_printf("input: |%s|\n", input);
    ft_sendall(fd, (uint8_t *)input, &len, 0);
    ft_strdel(&input);
}