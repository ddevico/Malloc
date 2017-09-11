#include "includes/malloc.h"


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


void    impress()
{
    t_page *ok;
printf("!!!!!!!!!!!!!!!!!!!!\n\nVoici le contenu de la globale\n\n");
    ok = g_page_one;
    while (ok)
    {
        printf("page = %lu SIZEOF(TBLOCK) === %lu \n", (long)ok, sizeof(t_block));
        while (ok->block != NULL)
        {
            
            printf("--->block = & =  %lu | str = '%s' %lu  | size = %lu\n", (long)ok->block, memory_plus(ok->block, sizeof(t_block)), (long)memory_plus(ok->block, sizeof(t_block)), ok->block->size);
            if (!ok->block->next)
                break;
            ok->block = ok->block->next;
        }
        ok = ok->next;
    }
printf("\n\n!!!!!!!!!!!!!!!!!!!!\n\n");
    
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

//sens de stockage: objet | t_block (de l'objet)
void *place(t_page *page, size_t size)
{
    size_t ecart;
    t_block *block;
    t_page *test;
//printf("place \n");

  //  printf("deuxieme boucle: ADD = %p | &add = %p \n", page, &page);
  printf("DEBUT\n\n");
  impress();
  printf("END DEBUT\n\n");
    test = page;
    ecart = 0;
    int i = 0;
    //page->busy += (size + sizeof(t_block));
    while (test->block && test->block->next)
        {
  //          printf("--------------------!!!!!!!!!!!!!!!\n\nBLOCK %d = %s, %p\n\n", i, memory_plus(test->block, sizeof(t_block)), test->block);
            test->block = test->block->next;
        }
    //printf("test->block = %lu | %lu | %lu\n\n", (long)test->block, test->block->size, (long)memory_plus(test->block, test->block->size));
    //printf("ORIGIN test == %lu\n", (long)g_test_one->block);
    block = memory_plus(test->block, test->block->size);
    block->size = size + sizeof(t_block);
    block->next = NULL;
    test->block->next = block;
    test->busy += block->size;
    // printf("RETOUR PLACE -------> %lu\n\n", (long)memory_plus(block, sizeof(t_block)));
printf("FIN\n\n");
  impress();
  printf("END FIN\n\n");
  --------------------------------------------
    //printf("\nbibi est laaaaaaaa %lu\n", (long)page->block);
    return (memory_plus(block, sizeof(t_block)));
}

//si pas de place trouvée
void *not_find(size_t size)
{
//printf("not find\n");
    
    t_page *origin;
    t_page *add;
    t_block *block;
    size_t size_type;

    origin = g_page_one;
    size_type = type_of_size(size);
//printf("1, size_type: %lu\n", size_type);
    //add = (t_page *)mmap(NULL, size_type, PROT_WRITE | PROT_READ, MAP_ANON | MAP_PRIVATE, -1, 0);
    add = mmap(NULL, size_type, PROT_WRITE | PROT_READ, MAP_ANON | MAP_PRIVATE, -1, 0);
    //printf("premier boucle : ADD = %p | &add = %p \n", add, &add);
    if (add == MAP_FAILED)
    {
        return (NULL);
    }
    add->busy = size + sizeof(t_page);
    add->size = size_type;
   // printf("calc %lu + %lu --> %lu\n", (long)add, sizeof(t_page), (long)memory_plus(add, sizeof(t_page)));
    block = memory_plus(add, sizeof(t_page));
    block->size = size + sizeof(t_block);
    block->next = NULL;
    add->block = block;
    add->next = NULL;
    printf("add->block =============== %p\n", add->block->next);
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
    //printf("DEPART: &page = %p | &block = %p  | size = %lu\n", add, block, block->size);
    //printf("premier boucle : Block = %p | &add = %p \n", g_page_one->block, block);
    //printf("premier boucle : Block = %p + size = %lu = %p \n", block, sizeof(t_block), memory_plus(block, sizeof(t_block)));
    
    return (memory_plus(block, sizeof(t_block)));
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
    //printf("-----------------\nG_PAGE_ONE = %p\n\n\nfirst = %d\n\n-------------------------------\n", g_page_one, first);

    origin = g_page_one; 
    printf("MY_MALLOC\n\n"); 
    impress();  
    printf("END   MY_MALLOC\n\n"); 
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
        impress();
    printf("chaine= %s\n", str);

        i++;
        y=0;
        x=0;
    }

    printf("essai %s\n", (char*)memory_plus(g_page_one->block, sizeof(t_block)));
    return (0);
}