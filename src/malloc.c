#include "malloc.h"

__attribute__((visibility("default")))
void *malloc(size_t __attribute__((unused)) size)
{
    size = adjust_size(size);
    struct p_meta *p_start = find_p_meta(size);
    if (!p_start)
    {
        return NULL;
    }
    uintptr_t *res = get_free_space(p_start);
    return res;
}

__attribute__((visibility("default")))
void free(void __attribute__((unused)) *ptr)
{
    if (!ptr)
    {
        return;
    }
    struct b_meta *b_meta = find_b_meta(ptr);
    struct p_meta *p_meta = find_p_meta(b_meta->size);
    if (!p_meta)
    {
        return;
    }
    new_free_ptr(p_meta, ptr);
}

__attribute__((visibility("default")))
void *realloc(void __attribute__((unused)) *ptr,
             size_t __attribute__((unused)) size)
{
    if (!ptr)
    {
        return malloc(size);
    }
    if (!size)
    {
        free(ptr);
        return NULL;
    }
    void *res = malloc(size);
    if (!res)
    {
        return NULL;
    }
    size_t old_size = find_b_meta(ptr)->size;
    if (size < old_size)
    {
        old_size = size;
    }
    memcpy(res, ptr, old_size);
    return res;
}

__attribute__((visibility("default")))
void *calloc(size_t __attribute__((unused)) nmemb,
             size_t __attribute__((unused)) size)
{
    void *ptr = malloc(size * nmemb);
    if (!ptr)
    {
        return NULL;
    }
    memset(ptr, 0, size * nmemb);
    return ptr;
}