#include "includes/malloc.h"

void *address_iterate(unsigned int max, void *addr)
{
    int i;

    i = 0;
    while (i < max)
    {
        addr++;
        i++;    
    }
    return (addr);

}
//y a t il a prevoir aussi une place pour le premier t_block?
size_t  type_of_size(size_t size)
{
    size_t val;

    if (size <= TINY)
    {
        //val = /*(TINY * */100 * getpagesize()/*)+ sizeof(t_page)*/;
        val = (TINY * 100)+ sizeof(t_page);
    }
    else if (size <= SMALL)
    {
//        val = (SMALL * 100 * getpagesize()) + sizeof(t_page);  
        val = (SMALL * 100)+ sizeof(t_page);
          
    }
    else
    {
//        val = (LARGE * 100 * getpagesize()) + sizeof(t_page);    
        val = (LARGE * 100)+ sizeof(t_page);
    
    }

    return (val);
}

//si pas de place trouvée
void *not_find(size_t size)
{
printf("not find\n");
    
    t_page *origin;
    t_page *add;
    t_block *block;
    size_t size_type;

printf("0\n");
    origin = g_page_one;
    size_type = type_of_size(size);
printf("1, size_type: %lu\n", size_type);
    //add = (t_page *)mmap(NULL, size_type, PROT_WRITE | PROT_READ, MAP_ANON | MAP_PRIVATE, -1, 0);
    add = mmap(NULL, size_type, PROT_WRITE | PROT_READ, MAP_ANON | MAP_PRIVATE, -1, 0);
if (add == MAP_FAILED)
{
    return (NULL);
}
//add = test;
    add->busy = size + sizeof(t_page);
printf("3\n");
    add->size = size_type;
    printf("calc %lu + %lu --> %lu", (long)&add, sizeof(t_page), (long)&add + sizeof(t_page));
    block = address_iterate(sizeof(t_page), &add);
    block->size = size + sizeof(t_block);
    block->next = NULL;
    add->block = block;
    add->next = NULL;
printf("4\n");
    while (origin && origin->next)
        origin = origin->next;
    if (g_page_one == NULL)
        g_page_one = add;
    else
        origin->next = add;
printf("&add(%p) + (t_page)%lu = &block(%p)\n", &add, sizeof(t_page), &block);
    
printf("5\n");
//printf("&add : %p|sizeof(add)=%lu | &var: %p|sizeof(var)=%lu \n", &add, sizeof(add), &block, size);
    
    return (address_iterate(sizeof(t_block), &block));
}


//sens de stockage: objet | t_block (de l'objet)
void *place(t_page *page, size_t size)
{
    size_t ecart;
    t_block *block;

    ecart = 0;
    page->busy += (size + sizeof(t_block));
    while (page->block->next)
        page->block = page->block->next;
    block = address_iterate(page->block->size, &page->block);
    block->size = size + sizeof(t_block);
    block->next = NULL;
    page->block->next = block;
    page->busy += block->size;

    return (&block);
}

void    *my_malloc(size_t size)
{
    static int first = 0;
    t_page *origin;

    if (first == 0)
    {
        g_page_one = NULL;
        first = 1;
    }
    origin = g_page_one;    
    while (origin)
    {
        if (origin->size - origin->busy >= size + sizeof(t_block))
            return (place(origin, size));
        origin = origin->next;
    }
printf("hello");
    return (not_find(size));
}

    int main(int ac, char **av)
{
    unsigned int nb = atoi(av[2]);
    char *str;
    int y = 0;
    int i = 0;

    while (i < nb)
    {
        printf("fois: %d", i);
         str = (char *)my_malloc(((sizeof(char)*strlen(av[1]))*nb)+1);
        int x = 0;
        while (x < strlen(av[1]))
        {
            str[y] = av[1][x];
            y++;
            x++;
        }
    str[y] = '\0';
    printf("%s\n", str);

        i++;
        x=0;
    }
    return (0);
}