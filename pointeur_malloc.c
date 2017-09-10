#include "includes/malloc.h"

//y a t il a prevoir aussi une place pour le premier t_block?
size_t  type_of_size(size_t size)
{
    size_t val;

    if (size <= TINY)
    {
        val = (TINY * 100 * getpagesize())+ sizeof(t_page);
    }
    else if (size <= SMALL)
    {
        val = (SMALL * 100 * getpagesize()) + sizeof(t_page);    
    }
    else
    {
        val = (LARGE * 100 * getpagesize()) + sizeof(t_page);    
    }

    return (val);
}

//si pas de place trouvée
void *not_find(size_t size)
{
printf("not find\n");
    
    t_page origin;
    t_page add;
    t_block block;
    size_t size_type;

printf("0\n");
    origin = g_page_one;
    size_type = type_of_size(size);
printf("1, size_type: %lu, %d\n", size_type, TINY);
    add = mmap(NULL, size_type, PROT_WRITE | PROT_READ, MAP_ANON | MAP_PRIVATE, -1, 0);
printf("2\n");
    add.busy = size + sizeof(t_page);
printf("3\n");
    add.size = size_type;
    add.address = &add;
    &block = add.address + size + sizeof(t_page);
    block.size = size + sizeof(t_block);
    block.address = add.address + sizeof(t_page);
    add.block = block;
    add.next = NULL;
printf("4\n");
    while (origin && origin.next)
        origin = origin.next;
    if (g_page_one == NULL)
        &g_page_one = add;
    else
        origin.next = &add;
printf("5\n");
    
    return (block.address);
}


//sens de stockage: objet | t_block (de l'objet)
void *place(t_page page, size_t size)
{
    size_t ecart;
    t_block block;

    ecart = 0;
    page.busy += (size + sizeof(t_block));
    while (page.block.next)
        page.block = page.block.next;
    block.size = size + sizeof(t_block);
    block.address = page.block.address + page.block.size;
    block.next = NULL;
    page.block.next = block;
    page.busy += block.size;

    return (block.address);
}

void    *my_malloc(size_t size)
{
    static int first = 0;
    t_page origin;

    if (first == 0)
    {
        g_page_one = NULL;
        first = 1;
    }
    origin = g_page_one;    
    while (origin)
    {
        if (origin.size - origin.busy >= size + sizeof(t_block))
            return (place(origin, size));
        origin = origin.next;
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