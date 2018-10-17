#include "malloc.h"

__attribute__((visibility("default")))
void *malloc(size_t __attribute__((unused)) size)
{
    size = adjust_size(size);
    struct p_meta *p_start = find_p_meta(size);
}

__attribute__((visibility("default")))
void free(void __attribute__((unused)) *ptr)
{
}

__attribute__((visibility("default")))
void *realloc(void __attribute__((unused)) *ptr,
             size_t __attribute__((unused)) size)
{
	return NULL;
}

__attribute__((visibility("default")))
void *calloc(size_t __attribute__((unused)) nmemb,
             size_t __attribute__((unused)) size)
{
	return NULL;
}