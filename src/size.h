#ifndef SIZE_H
# define SIZE_H

#include <stdint.h>
#include <string.h>

#define NB_SIZE 8
enum size
{
    s_16 = 1,
    s_32,
    s_64,
    s_128,
    s_256,
    s_512,
    s_1024,
    s_unknown
};

size_t align_size(size_t size);
size_t adjust_size(size_t size);
enum size size_to_enum(size_t size);

#endif /* !SIZE_H */