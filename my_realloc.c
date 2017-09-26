#include "includes/malloc.h"

void *try_to_realloc(t_page *first, t_block *one, void *ptr, size_t size)
{
    void *next;

    if (size == 0 && ptr != NULL)
    {
        my_free(ptr);
        return ((void *)42);
    }
    if (one->size - sizeof(t_block) >= size)
    {
        one->busy = size;
        return (ptr);
    }
    else if (one->next && (one->next)->busy == 0 && one->size + (one->next)->size - sizeof(t_block) >= size)
    {
        one->size += (one->next)->size;
        one->busy = size;
        one->next = (one->next)->next;
        return (ptr);
    }
    else
    {
        printf("3eme cas \n\n");
        next = my_malloc(size);
        ft_memcpy(next, ptr, ((size < one->busy) ? size : one->busy));
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
            if (ptr && ptr == memory_plus(first->block, sizeof(t_block)))
             {
                ptr = try_to_realloc(first, first->block, ptr, size);
                first->block = one;
                break;
             }    
            first->block = first->block->next;            
        }           
        first->block = one;
        first = first->next;
    }
    first = g_page_one;

    return ((ptr == NULL) ? my_malloc(size) : ptr);
}