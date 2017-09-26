#include "includes/malloc.h"

void    *my_calloc(size_t nmemb, size_t size)
{
    void *ptr;

    ptr = my_malloc(nmemb * size);
    if (ptr)
        ft_bzero(ptr, nmemb * size);
    return (ptr);
}