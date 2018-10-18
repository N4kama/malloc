#include "setup.h"

void *g_head;

void setup_f_list(void *f_list)
{
    struct f_meta *f_meta = f_list;
    f_meta->prev = f_meta;
    f_meta->next = f_meta;
}

void allocate_new_page(struct p_meta *p_meta)
{
    void *addr = mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_PRIVATE
		      | MAP_ANONYMOUS, -1, 0);
    struct b_meta *page = addr;
    page->size = p_meta->size;
    if (!p_meta->next)
    {
	p_meta->next = addr;
	p_meta->prev = addr;
    }
    page->prev = p_meta->next;
    page->next = p_meta->prev;
    p_meta->prev = page;
    p_meta->f_list = caster(page + 1);
    setup_f_list(p_meta->f_list);
}

void create_page_meta(size_t size)
{
    struct sized_f_list_meta *meta = get_head();
    struct p_meta *p_meta = caster(meta + 1);
    for (size_t i = 0; i < meta->count_sized_list; p_meta += 1)
    {
	p_meta->size = size;
	p_meta->prev = NULL;
	p_meta->next = NULL;
	p_meta->f_list = NULL;
    }
}

static void *create_head(void)
{
    void *addr = mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_PRIVATE
		      | MAP_ANONYMOUS, -1, 0);
    struct sized_f_list_meta *meta = addr;
    meta->count_sized_list = 0;
    return addr;
}

void *get_head(void)
{
    if (g_head)
    {
	return g_head;
    }
    g_head = create_head();
    return g_head;
}
