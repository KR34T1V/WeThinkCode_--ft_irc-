#include "../inc/private_irc.h"

void c_getinput(int fd){
    int len;
    char *input;

    ft_get_next_line(STDIN_FILENO, &input);
    len = ft_strlen(input);
    input[len - 1] = '\0';
    ft_printf("input: |%s|\n", input);
    //replace \n
    ft_sendall(fd, (uint8_t *)input, &len, 0);
    ft_strdel(&input);
}