#include "includes/malloc.h"

void *try_to_realloc(t_page *first, t_block *one, void *ptr, size_t size)
{
    void *next;
    int i;

    if (one->size - sizeof(t_block) >= size)
        return (ptr);
    else if (one->next && (one->next)->busy == 0 && one->size + (one->next)->size - sizeof(t_block) >= size)
    {
        one->size += (one->next)->size;
        one->busy = size;
        one->next = (one->next)->next;
        return ptr;
    }
    else
    {
        i=-1;
        next = my_malloc(size);
        while (++i < one->busy)
            next[i] = ptr[i];
        my_free(ptr);
        return(next);
    }
}

void *my_realloc(void *ptr, size_t size)
{
    t_page *first;
    t_block *one;
    
    first = g_page_one;
    while (first)
    {
        one = first->block;
        while (first->block != NULL)
        {
            if (ptr == memory_plus(first->block, sizeof(t_block)))
                return (try_to_realloc(first, first->block, ptr, size));
            first->block = first->block->next;            
        }           
        first->block = one;
        first = first->next;
    }

    return(NULL);
}