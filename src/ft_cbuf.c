#include "../inc/private_cbuf.h"
#include "../inc/export_cbuf.h"
/*
    Assigns pointes so that they will overwrite data.
*/
static void cbuf_adv_pointer(t_cbuf cbuf)
{
	assert(cbuf);

	if(cbuf->full)
   	{
		cbuf->tail = (cbuf->tail + 1) % cbuf->max;
	}

	cbuf->head = (cbuf->head + 1) % cbuf->max;
	cbuf->full = (cbuf->head == cbuf->tail);
}

static void cbuf_follow_pointer (t_cbuf cbuf)
{
	assert(cbuf);

	cbuf->full = false;
	cbuf->tail = (cbuf->tail + 1) % cbuf->max;
}

/*
    Pass in a storage buffer and size 
    Returns a circular buffer handle
*/
t_cbuf  cbuf_init(uint8_t* buffer, size_t size){
    t_cbuf cbuf;
    
    assert(buffer && size);
    cbuf = ft_memalloc(sizeof(t_cbuf_actual));
    assert(cbuf);
    cbuf->buffer = buffer;
    cbuf->max = size;
    cbuf_reset(cbuf);
    assert(cbuf_isempty(cbuf));
    return (cbuf);
}

/*
    Frees and clears the circular buffer "cbuf".
    Does not free data buffer;
*/
void    cbuf_free(t_cbuf cbuf){
    
    assert(cbuf);
    ft_memdel((void**)&cbuf);
}

/*
Reset the circular buffer "cbuf" to empty, head == tail
*/
void    cbuf_reset(t_cbuf cbuf){
    assert(cbuf);
    
    cbuf->head = 0;
    cbuf->tail = 0;
    cbuf->full = 0;
}

/*
Adds data to the buffer
Old data can be overwritten
Returns -1 if buffer is full and overwrite paramater set to "false".
Returns 0 on success.
*/
int    cbuf_put(t_cbuf cbuf, uint8_t data, bool overwrite){
    assert(cbuf && cbuf->buffer);
    if (overwrite){
        if (!cbuf_isfull(cbuf)){
            cbuf->buffer[cbuf->head] = data;
            cbuf_adv_pointer(cbuf);
            return (0);
        }
        return (-1);
    }
    cbuf->buffer[cbuf->head] = data;
    cbuf_adv_pointer(cbuf);
    return (0);
}

/*
Retrieve a value from the buffer
Returns 0 on success, -1 if the buffer is empty
*/
int     cbuf_get(t_cbuf cbuf, uint8_t * data){
    assert(cbuf && cbuf->buffer && data);

    if (!cbuf_isempty(cbuf)){
        *data = cbuf->buffer[cbuf->tail];
        cbuf_follow_pointer(cbuf);
        return (0);
    }
    return (-1);
}

/*
Returns true if the buffer is empty
*/
bool    cbuf_isempty(t_cbuf cbuf){
    assert(cbuf);
    if  (cbuf->head == cbuf->tail && !cbuf->full)
        return (1);
    return (0);
}

/*
Returns true if the buffer is full
*/
bool    cbuf_isfull(t_cbuf cbuf){
    assert(cbuf);
    return(cbuf->full);
}

/*
Returns the maximum size of the buffer
*/
size_t  cbuf_max(t_cbuf cbuf){
    assert(cbuf);
    return(cbuf->max);
}

/*
Returns the current number of elements in the buffer
*/
size_t  cbuf_size(t_cbuf cbuf){
    assert(cbuf);
    if (!cbuf->full){
        if (cbuf->head > cbuf->tail){
            return(cbuf->head - cbuf->tail);
        }
        return (cbuf->tail - cbuf->head);
    }
    return(cbuf->tail - cbuf->head);
}