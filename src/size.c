#include "size.h"

size_t align_size(size_t size)
{
    return (size + sizeof(size_t) - 1) & ~(sizeof(size_t) - 1);
}

size_t adjust_size(size_t size)
{
    if (size < 16)
    {
	return 16;
    }
    
    size--;
    size |= size >> 1;
    size |= size >> 2;
    size |= size >> 4;
    size |= size >> 8;
    size |= size >> 16;
    size++;
    return size;
}

size_t get_page_addr(size_t b_addr)
{
    size_t res = b_addr;
    res &= (1 << 11) - 1;
    return res;
}