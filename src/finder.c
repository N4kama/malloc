#include "finder.h"

unsigned int no_space_in_page(struct p_meta *p_meta, size_t last_f_block)
{
    //No space in page if there is not enough space to put a new block
    size_t addr = last_f_block;
    size_t start = get_page_addr(addr);
    size_t next = last_f_block + p_meta->size;
    size_t new_start = get_page_addr(next);
    if (start == new_start)
    {
	return 1;
    }
    return 0;
}

void update_free_ptr(struct p_meta *p_meta)
{
    size_t *f_list = caster(p_meta->f_list);
    if (no_space_in_page(p_meta, *f_list))
    {
	p_meta->f_list = NULL;
    }
    else
    {
	struct f_meta *f_meta = p_meta->f_list;
	struct f_meta *new = f_meta + 1;
	if (f_meta->prev == f_meta->next)
	{
	    //Last ptr was the only one, the new one is also solo then
	    setup_f_list(new);
	}
	else
	{
	    new->next = f_meta;
	    new->prev = f_meta->prev;
	    f_meta->prev->next = new;
	    f_meta->prev = new;
	}
	p_meta->f_list = new;
    }
}

struct p_meta *find_p_meta(size_t size)
{
    struct sized_f_list_meta *sized_l = get_head();
    struct p_meta *meta = caster(sized_l + 1);
    unsigned int i = 0;
    for (; i < sized_l->count_sized_list; i++)
    {
	if (meta->size == size)
	{
	    break;
	}
	meta += 1;
    }
    if (i == sized_l->count_sized_list)
    {
	create_page_meta(size);
    }
    return meta;
}

void *get_free_space(struct p_meta *p_meta)
{
    if (!p_meta->f_list)
    {
	allocate_new_page(p_meta);
    }
    void *free_ptr = p_meta->f_list;
    update_free_ptr(p_meta);
    return free_ptr;
}