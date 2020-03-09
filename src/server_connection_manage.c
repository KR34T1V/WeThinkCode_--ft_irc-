#include "../inc/private_irc.h"


int server_connection_manage(int fd, int fd_max, fd_set *readfds, fd_set *connections){
    int                 accepted_fd;
    int                 i;


    while(1){
        i = 0;
        while(i <= fd_max){
            if (FD_ISSET(i, readfds)){
                if (i == fd){
                    if ((accepted_fd = server_connection_accept(i)) != -1){
                        FD_SET(fd, connections);
                        if (accepted_fd > fd_max)
                            fd_max = accepted_fd;
                        ft_printf("connection accepted on fd: %d\n", accepted_fd);
                    }
                } else {
                    ft_printf("Possible Message On fd: %d\n", i);
                }
            }
        i++;
        }
        ft_printf("Timed Out...\n");
    }
    return(1);
}