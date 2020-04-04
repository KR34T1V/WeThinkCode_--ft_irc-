#include "../inc/private_irc.h"

void c_getinput(int fd){
    int len;
    char *input;

    ft_get_next_line(STDIN_FILENO, &input);
    len = ft_strlen(input);
    input[len] = '\0';
    ft_printf("input: %s", input);
    //replace \n
    ft_sendall(fd, input, &len, 0);
    ft_strdel(&input);
}