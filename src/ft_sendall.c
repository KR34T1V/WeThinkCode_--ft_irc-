#include "../inc/private_irc.h"

/*
    Ensures that all data in "buf" is successfully sent to "fd", returns 0 on success
    ammends "len" to match the total amount of data sent. Returns -1 on failure.
*/
int ft_sendall(int fd, char *buf, int *len, int flags)
{
    int total = 0;
    int bytesleft = *len;
    int n;
    printf("Sending to %d: %s\n", fd, buf);
    while(total < *len) {
        n = send(fd, buf+total, bytesleft, flags);
        if (n == -1)
            break;
        total += n;
        bytesleft -= n;
    }
    *len = total;
    return n==-1?-1:0;
}