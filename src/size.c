#include "size.h"

size_t align_size(size_t size)
{
    return (size + sizeof(size_t) - 1) & ~(sizeof(size_t) - 1);
}

size_t adjust_size(size_t size)
{
    size--;
    size |= size >> 1;
    size |= size >> 2;
    size |= size >> 4;
    size |= size >> 8;
    size |= size >> 16;
    size++;
    return size;
}

enum size size_to_enum(size_t size)
{
    for (unsigned int i = 1; i < NB_SIZE; i++)
    {
	if (size == (1 << (3 + i)))
	{
	    return i;
	}
    }
    return 8;
}
