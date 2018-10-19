#ifndef SIZE_H
# define SIZE_H

#include <stdint.h>
#include <string.h>

size_t align_size(size_t size);
size_t adjust_size(size_t size);
size_t get_page_addr(size_t b_addr);
size_t get_page_size(size_t size);

#endif /* !SIZE_H */