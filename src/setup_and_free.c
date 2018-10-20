#include "setup_and_free.h"

void *g_head;

void setup_f_list(void *f_list)
{
    struct f_meta *f_meta = f_list;
    f_meta->prev = f_meta;
    f_meta->next = f_meta;
}

static struct b_meta *update_nb_blk(struct f_meta *f_meta)
{
    //Update nb_blk in page -> minus 1
    uintptr_t addr = cast_to_ptr(f_meta);
    uintptr_t page_addr = get_page_addr(addr);
    struct b_meta *res = cast_to_void(page_addr);
    res->nb_blk -= 1;
    return res;
}

/*static unsigned int free_struct(struct p_meta *p_meta, struct b_meta *b_meta)
{
    //free the page corresponding to f_meta
    //if no pages left, it will also free the meta struct in the header
    size_t size = get_page_size(b_meta->size);
    if (b_meta->next != b_meta)
    {
        b_meta->prev->next = b_meta->next;
        b_meta->next->prev = b_meta->prev;
        munmap(b_meta, size);
	
    }
    //todo : handle the freeing in the meta struct header
    }*/

void new_free_ptr(struct p_meta *p_meta, struct f_meta *f_meta)
{
    //struct b_meta *b_meta =
    update_nb_blk(f_meta);
    /*if (!b_meta->nb_blk)
    {
        free_struct(p_meta, b_meta);
        return;
	}*/
    //relink the new block with the old f_list
    if (!p_meta->f_list)
    {
        //Free dans le cas ou la struct est pleine (pas assez de place pour un
        //deuxieme block). Le ptr_free est null, f_meta devient ptr_free
        setup_f_list(f_meta);
        p_meta->f_list = f_meta;
    }
    else
    {
        f_meta->next = p_meta->f_list;
        f_meta->prev = p_meta->f_list->prev;
        p_meta->f_list->prev->next = f_meta;
        p_meta->f_list->prev = f_meta;
        p_meta->f_list = f_meta;
    }
}

unsigned int  allocate_new_page(struct p_meta *p_meta)
{
    size_t len = p_meta->size + sizeof(struct b_meta);
    void *addr = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_PRIVATE
                      | MAP_ANONYMOUS, -1, 0);
    if (addr == MAP_FAILED)
    {
	return 0;
    }
    struct b_meta *page = addr;
    page->size = p_meta->size;
    if (!p_meta->next)
    {
        p_meta->next = addr;
        p_meta->prev = addr;
    }
    page->prev = p_meta->next;
    page->next = p_meta->prev;
    page->nb_blk = 0;
    p_meta->prev = page;
    p_meta->f_list = caster(page + 1);
    setup_f_list(p_meta->f_list);
    return 1;
}

static unsigned int check_head_size(struct sized_f_list_meta **metaa)
{
    struct sized_f_list_meta *meta = *metaa;
    size_t page_meta_len = meta->count_sized_list * sizeof(struct p_meta);
    page_meta_len += sizeof(struct sized_f_list_meta);
    if (page_meta_len + sizeof(struct p_meta) > meta->page_len)
    {
	//resize page
	void *new = mmap(NULL, 2 * meta->page_len, PROT_READ | PROT_WRITE,
			 MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (new == MAP_FAILED)
	{
	    return 0;
	}
	memcpy(new, meta, meta->page_len);
	munmap(meta, meta->page_len);
	*metaa = new;
	(*metaa)->page_len *= 2;
	g_head = new;
    }
    return 1;
}

unsigned int create_page_meta(size_t size)
{
    struct sized_f_list_meta *meta = get_head();
    if (!check_head_size(&meta))
    {
	return 0;
    }
    struct p_meta *p_meta = caster(meta + 1);
    for (size_t i = 0; i < meta->count_sized_list; i++)
    {
        p_meta += 1;
    }
    p_meta->size = size;
    p_meta->prev = NULL;
    p_meta->next = NULL;
    p_meta->f_list = NULL;
    meta->count_sized_list += 1;
    return 1;
}

static void *create_head(void)
{
    void *addr = mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_PRIVATE
                      | MAP_ANONYMOUS, -1, 0);
    if (addr == MAP_FAILED)
    {
	return NULL;
    }
    struct sized_f_list_meta *meta = addr;
    meta->page_len = 4096;
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
