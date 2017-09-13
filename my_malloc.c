#include "includes/malloc.h"


int nb;

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


size_t  type_of_size(size_t size)
{
    size_t val;

    if (size <= TINY)
    {
        val = (TINY * 100)+ sizeof(t_page);
    }
    else if (size <= SMALL)
    {
        val = (SMALL * 100)+ sizeof(t_page);

    }
    else
    {
        val = (LARGE * 100)+ sizeof(t_page);
    }
    return (val);
}

void *place(t_page page, size_t size)
{
    size_t ecart;
    t_block *block;
    t_page *test;
    t_page *tmp;
    test = &page;
    ecart = 0;
    int i = 0;
    while (test->block && test->block->next)
        {
            test->block = test->block->next;
        }
    block = memory_plus(test->block, test->block->size);
    block->size = size + sizeof(t_block);
    block->next = NULL;
    test->block->next = block;
    test->busy += block->size;
    //printf("%zu\n", test->busy);
    //printf("g_page_one: %zu\n", g_page_one->block->size);
    return (memory_plus(block, sizeof(t_block)));
}

void *not_find(size_t size)
{
    t_page *origin;
    t_page *add;
    t_block *block;
    size_t size_type;
    origin = g_page_one;
    size_type = type_of_size(size);
    add = mmap(NULL, size_type, PROT_WRITE | PROT_READ, MAP_ANON | MAP_PRIVATE, -1, 0);
    if (add == MAP_FAILED)
    {
        return (NULL);
    }
    add->busy = size + sizeof(t_page) + sizeof(t_block);
    add->size = size_type;
    block = memory_plus(add, sizeof(t_page));
    block->size = size + sizeof(t_block);
    block->next = NULL;
    add->block = block;
    add->next = NULL;
    while (origin && origin->next)
        origin = origin->next;
    if (g_page_one == NULL)
        g_page_one = add;
    else
        origin->next = add;
    //g_page_one = g_page_one->next;
    return (memory_plus(block, sizeof(t_block)));
}

void    *my_malloc(size_t size)
{
    static int first = 0;
    t_page *origin;
    t_page *tmp;


    if (first == 0)
    {
        g_page_one = NULL;
        first = 1;
    }
    origin = g_page_one;
    nb++;
    //printf("n = %d\n", nb);
    while (origin)
    {
        if (origin->size - origin->busy >= size + sizeof(t_block))
        {
          origin->busy += (size + sizeof(t_block));
          return (place(*origin, size));
        }
        origin = origin->next;
    }
    return (not_find(size));
}

int main(int ac, char **av)
{

  nb = 1;
  unsigned int nb = atoi(av[2]);
  char *str;
  int y = 0;
  int i = 0;

  while (i < nb)
  {
      //printf("fois: %d", i);
      str = (char *)my_malloc(((sizeof(char)*strlen(av[1]))*nb)+1);
      int x = 0;
      while (x < strlen(av[1]))
      {
          str[y] = av[1][x];
          y++;
          x++;
      }
      str[y] = '\0';
      i++;
      x=0;
      y = 0;
  }
  int n= 0;
  while (g_page_one)
  {
    n++;
    g_page_one = g_page_one->next;
  }
  printf("%d\n", n);
    //impress();
  return (0);
}
