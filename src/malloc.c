#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <pthread.h>
#include <stdint.h>

extern int *g_head;

static size_t align_size(size_t size)
{
    return (size + sizeof(size_t) - 1) & ~(sizeof(size_t) - 1);
}

__attribute__((visibility("default")))
void *malloc(size_t __attribute__((unused)) size)
{
	return NULL;
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

int main(void)
{
    for (int i = 0; i <= 20; i++)
	printf("%d : %lu\n", i, align_size(i));
}