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
    if (size > 1024)
    {
        return align_size(size);
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

uintptr_t get_page_addr(uintptr_t b_addr)
{
    b_addr = b_addr >> 12;
    b_addr = b_addr << 12;
    return b_addr;
}