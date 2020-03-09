#include "../inc/private_irc.h"

/*
    Attempts to bind a socket to a file descriptor, If successfull the file descriptor is returned, else -1 is returned.
    setspockopt() prevents "address already in use" error message
*/

int server_bindaddr(char *port){
    int listener;
    int yes;
    struct addrinfo* head;
    struct addrinfo* runner;
    
    yes =1;
    head = server_getaddrinfo(port);
    runner = head;
    while (runner != NULL){
        listener = socket(runner->ai_family,runner->ai_socktype,runner->ai_protocol);
        setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
        if (listener == -1){
            runner = runner->ai_next;
            continue;
        }
        if (bind(listener, runner->ai_addr, runner->ai_addrlen) == 0)
            break;
        close(listener);
        runner = runner->ai_next;
    }
    freeaddrinfo(head);
    if (runner == NULL){
        ft_printf("Could not bind socket!\n");
        perror("bindaddr");
        _exit(1);
    } else
        return listener;
}