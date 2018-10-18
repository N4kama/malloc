#include "malloc.h"

__attribute__((visibility("default")))
void *malloc(size_t __attribute__((unused)) size)
{
    size = adjust_size(size);
    struct p_meta *p_start = find_p_meta(size);
    uintptr_t *res = get_free_space(p_start);
    return res;
}

__attribute__((visibility("default")))
void free(void __attribute__((unused)) *ptr)
{
    struct b_meta *b_meta = find_b_meta(ptr);
    struct p_meta *p_meta = find_p_meta(b_meta->size);
    new_free_ptr(p_meta, ptr);
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