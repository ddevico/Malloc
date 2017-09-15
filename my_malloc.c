#include "includes/malloc.h"


int pages;

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
    int x = 0;
    t_page *ok;
    t_block *oki;
    printf("!!!!!!!!!!!!!!!!!!!!\n\nVoici le contenu de la globale\n\n");
    ok = g_page_one;
    while (ok)
    {

        printf("page = %lu || SIZE === %lu  ||| busy = %lu ||| sizeof(t_page) = %lu\n", (long)ok, ok->size, ok->busy, sizeof(t_page));
        oki = ok->block;
        while (ok->block != NULL)
        {
            if (x==0)
            {
            printf("$$$$$$1er--->Decalage de 16 ou  plus entre ça et le debut --> block = & %lu | str = '%s' & %lu (a + b %% 16) | size = %lu\n", (long)ok->block, memory_plus(ok->block, sizeof(t_block)), (long)memory_plus(ok->block, sizeof(t_block)), ok->block->size);
                
                x++;
            }else
                printf("--->block = & %lu | str = '' & %lu (a + b %% 16) | size = %lu\n", (long)ok->block,  (long)memory_plus(ok->block, sizeof(t_block)), ok->block->size);

            if (!ok->block->next)
                break;
            ok->block = ok->block->next;
        }
        ok->block = oki;
        x=0;
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

void    *busyness(t_page page, size_t size, int busy)
{
    t_block *block;
    
    while (busy-- != 1)
        page.block = page.block->next;
    if (page.block->busy == 0 && page.block->size - sizeof(t_block) >= size)
    {
        page.block->busy += size;
        return (memory_plus(page.block, sizeof(t_block)));
    }
    else
    {
        block = memory_plus(page.block, sizeof(t_block) + page.block->busy);
        block->size = page.block->size - page.block->busy - sizeof(t_block);
        block->busy = size;
        page.block->size -= block->size;
        
        block->next = page.block->next;
        page.block->next = block;
        return (memory_plus(block, sizeof(t_block)));
    }
}

void *place(t_page page, size_t size, int busy)
{
    size_t ecart;
    t_block *block;
    t_page *test;

    test = &page;
    if ((busy = busy_precision(test, busy)) > 0)
        return (busyness(*test, size, busy));
    ecart = 0;
    int i = 0;
    while (test->block && test->block->next)
        {
            test->block = test->block->next;
        }
    block = memory_plus(test->block, test->block->size);
    block->size = (size + sizeof(t_block));
    block->busy = size;
    block->next = NULL;
    test->block->next = block;
    test->busy += block->size;
    return (memory_plus(block, sizeof(t_block)));
}

void *not_find(size_t size)
{
    pages++;
    
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
    block->busy = size;
    block->next = NULL;
    add->block = block;
    add->next = NULL;
    while (origin && origin->next)
        origin = origin->next;
    if (g_page_one == NULL)
        g_page_one = add;
    else
        origin->next = add;
    return (memory_plus(block, sizeof(t_block)));
}

void    *my_malloc(size_t size)
{
    static int  first = 0;
    int         busy;
    t_page      *origin;

    busy = 0;
    if (first == 0)
    {
        g_page_one = NULL;
        first = 1;
    }
    origin = g_page_one;
    while (origin)
    {
        if (origin->size - origin->busy >= size + sizeof(t_block) && (busy = busy_question(origin, size)) != -1)
        {
          //busy = -1-->no place || 0->size | 1 --> size +t_block
          origin->busy += ((busy == 0) ? size : (size + sizeof(t_block)));
          return (place(*origin, size, busy));
        }
        origin = origin->next;
    }
    return (not_find(size));
}

int main(int ac, char **av)
{
    int tour = 0;
  pages = 0;
  int ok = pages;
  unsigned int nb = atoi(av[2]);
  char *str;
  int y = 0;
  int i = 0;
g_page_one = NULL;
  while (i < nb)
  {
      if (ok != pages){
          ok = pages;
   // impress();
      }
      str = (char *)my_malloc((sizeof(char)*strlen(av[1]))+1);
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
      tour++;
      if (tour % 50 == 0)
        my_free(str);
  }

  return (0);
}
