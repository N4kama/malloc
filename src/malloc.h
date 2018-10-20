#ifndef MALLOC_H
# define MALLOC_H

#include <string.h>
#include <stdint.h>

#include "finder.h"

__attribute__((visibility("default")))
void *malloc(size_t __attribute__((unused)) size);

__attribute__((visibility("default")))
void free(void __attribute__((unused)) *ptr);

__attribute__((visibility("default")))
void *realloc(void __attribute__((unused)) *ptr,
              size_t __attribute__((unused)) size);

__attribute__((visibility("default")))
void *calloc(size_t __attribute__((unused)) nmemb,
             size_t __attribute__((unused)) size);

#endif /* !MALLOC_H */