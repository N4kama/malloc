#include "setup.h"

extern void *g_head;

static void *create_head(void)
{
    void *addr = mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_PRIVATE
		      | MAP_ANONYMOUS, -1, 0);
    struct p_meta *p_meta = addr;
    for (size_t i = 0; i < NB_SIZE; i++)
    {
	p_meta->size = i;
	p_meta->f_list = NULL;
	p_meta += 1;
    }
    return addr;
}

extern void *get_head(void)
{
    if (g_head)
    {
	return g_head;
    }
    g_head = create_head();
    return g_head;
}
