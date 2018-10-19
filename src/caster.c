#include "caster.h"

void *caster(void *ptr)
{
    return ptr;
}

uintptr_t cast_to_ptr(void *elm)
{
    return (uintptr_t)elm;
}

void *cast_to_void(uintptr_t elm)
{
    return (void *)elm;
}