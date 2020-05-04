#ifndef PRIVATE_CBUF_H
# define PRIVATE_CBUF_H

#include <assert.h>
#include "./export_cbuf.h"
#include "../lib/printf/inc/export_ft_printf.h"
#include <stdlib.h>
#include <sys/types.h>
#include <inttypes.h>
#include <stdbool.h>

struct s_cbuf{
    uint8_t     *buffer;
    size_t      head;
    size_t      tail;
    size_t      max;
    bool        full; 
};

#endif