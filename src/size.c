#include "size.h"

size_t align_size(size_t size)
{
    return (size + sizeof(size_t) - 1) & ~(sizeof(size_t) - 1);
}

enum size asjust_size(size_t size)
{
    
}
