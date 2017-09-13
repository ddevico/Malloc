#include "includes/malloc.h"


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

void *memory_plus(void *addr, size_t inc)
{
    int i;

    i=0;
    while (i < inc)
    {
        addr++;
        i++;
    }
    return (addr);
}

//si pas de place trouvée
void *not_find(size_t size)
{
printf("not find\n");
    
    t_page *origin;
    t_page *add;
    t_block *block;
    size_t size_type;

//printf("0\n");
    origin = g_page_one;
    size_type = type_of_size(size);
//printf("1, size_type: %lu\n", size_type);
    //add = (t_page *)mmap(NULL, size_type, PROT_WRITE | PROT_READ, MAP_ANON | MAP_PRIVATE, -1, 0);
    add = mmap(NULL, size_type, PROT_WRITE | PROT_READ, MAP_ANON | MAP_PRIVATE, -1, 0);
if (add == MAP_FAILED)
{
    return (NULL);
}
//add = test;
    add->busy = size + sizeof(t_page);
//printf("3\n");
    add->size = size_type;
    printf("calc %lu + %lu --> %lu\n", (long)add, sizeof(t_page), (long)memory_plus(add, sizeof(t_page)));
    block = (void *)(add + sizeof(t_page));
    block->size = size + sizeof(t_block);
    block->next = NULL;
    add->block = block;
    add->next = NULL;
//printf("4\n");
    while (origin && origin->next)
        origin = origin->next;
    if (g_page_one == NULL)
        g_page_one = add;
    else
        origin->next = add;
//printf("&add(%p) + (t_page)%lu = &block(%p)\n", &add, sizeof(t_page), &block);
    
//printf("5\n");
//printf("&add : %p|sizeof(add)=%lu | &var: %p|sizeof(var)=%lu \n", &add, sizeof(add), &block, size);
    printf("DEPART: &page = %p | &block = %p  | size = %lu\n", add, block, block->size);
    return ((void*)(block+ sizeof(t_block)));
}


//sens de stockage: objet | t_block (de l'objet)
void *place(t_page *page, size_t size)
{
    size_t ecart;
    t_block *block;
    t_page *bis;
printf("place \n");

bis = page;
    ecart = 0;
    int i = 0;
    //page->busy += (size + sizeof(t_block));
    while (bis->block->next)
        {
            //printf("while = %d\n\n", i);
            bis->block = bis->block->next;
        }
    printf("page->block = %lu | %lu | %lu\n\n", (long)bis->block, bis->block->size, (long)memory_plus(bis->block, bis->block->size));
    block = (void *)memory_plus(bis->block, bis->block->size);
    block->size = size + sizeof(t_block);
    block->next = NULL;
    bis->block->next = block;
    bis->busy += block->size;

    return ((void*)(memory_plus(block, sizeof(t_block))));
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
    printf("chaine= %s\n", str);

        i++;
        x=0;
    }

    printf("essai %s\n", (g_page_one->block + sizeof(t_block)));
    return (0);
}