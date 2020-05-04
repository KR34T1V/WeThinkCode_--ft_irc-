/*
    Resources:

    Circular Buffers
        https://embeddedartistry.com/blog/2017/05/17/creating-a-circular-buffer-in-c-and-c/
*/

#ifndef CIRCULAR_BUF_H
# define CIRCULAR_BUF_H
#include <stdbool.h>
#include <sys/types.h>
#include <inttypes.h>

typedef struct s_cbuf t_cbuf_actual;
typedef t_cbuf_actual *t_cbuf;

/*
    Pass in a storage buffer and size 
    Returns a circular buffer handle
*/
t_cbuf  ft_cbuf_init(uint8_t* buffer, size_t size);

/*
    Free a circular buffer structure.
    Does not free data buffer; owner is responsible for that
*/
void    ft_cbuf_free(t_cbuf cbuf);

/*
Reset the circular buffer to empty, head == tail
*/
void    ft_cbuf_reset(t_cbuf cbuf);

/*
Adds data to the buffer
Old data can be overwritten
Returns -1 if buffer is full and overwrite paramater set to "false".
Returns 0 on success.
*/
int    ft_cbuf_put(t_cbuf cbuf, uint8_t data, bool overwrite);

/*
Retrieve a value from the buffer
Returns 0 on success, -1 if the buffer is empty
*/
int     ft_cbuf_get(t_cbuf cbuf, uint8_t * data);

/*
Returns true if the buffer is empty
*/
bool    ft_cbuf_isempty(t_cbuf cbuf);
/*
Returns true if the buffer is full
*/
bool    ft_cbuf_isfull(t_cbuf cbuf);

/*
Returns the maximum size of the buffer
*/
size_t  ft_cbuf_max(t_cbuf cbuf);

/*
Returns the current number of elements in the buffer
*/
size_t  ft_cbuf_size(t_cbuf cbuf);
#endif