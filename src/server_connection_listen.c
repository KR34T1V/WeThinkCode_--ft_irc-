#include "../inc/private_irc.h"

int server_connection_listen(int fd, fd_set *connections){
    int                 new_fd;
    int                 fd_max;
    fd_set              readfds;

    if (fd >= FD_SETSIZE) {
        ft_printf("Socket cannot be used on a file descriptor larger then: %d\n", FD_SETSIZE);
        return (-1);
    }
    ft_printf("Listening on fd %d\n", fd);
    if(listen(fd, SERVER_LISTEN_BACKLOG) == -1) {
        ft_printf("Failed to listen on fd: %d\n", fd);
        return (-1);
    }
    FD_SET(fd, connections);
    fd_max = fd;
    while(1){
        readfds = *connections;
        if (select(fd_max + 1, &readfds, NULL, NULL, NULL) == -1)
            return (-1);
        ft_printf("Listening for new connections...\n");
        new_fd = server_connection_manage(fd, fd_max, &readfds, connections);
        FD_SET(fd, connections);
        if (new_fd > fd_max)
            fd_max = new_fd;
        return new_fd;
    }
}