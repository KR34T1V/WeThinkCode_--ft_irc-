#include "../inc/private_irc.h"

int server_connection_accept(int fd){
    int                 accepted_fd;
    struct sockaddr_in  client_socket;
    socklen_t           client_socket_length;

    client_socket_length = sizeof(client_socket);
    accepted_fd = accept(fd,(struct sockaddr *)&client_socket, &client_socket_length);
    if (accepted_fd == -1){
        ft_printf("Failed to accept connection!\n");
        return (-1);
    } else {
    ft_printf("Accepted fd: %i\n", accepted_fd);
    return (accepted_fd);
    }
}