#ifndef CASTER_H
# define CASTER_H

#include <stdint.h>

void *caster(void *ptr);
uintptr_t cast_to_ptr(void *elm);
void *cast_to_void(uintptr_t elm);

#endif /* !CASTER_H */