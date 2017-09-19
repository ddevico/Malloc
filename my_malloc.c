#include "includes/malloc.h"


int pages;

int     types_of_var(size_t page, size_t size)
{
    size = type_of_size(size);
    if (page == size && size != ((LARGE * 100)+ sizeof(t_page)))
        return (1);
    return (0);
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



void    impress()
{
    int x = 0;
    t_page *ok;
    t_block *oki;
    printf("!!!!!!!!!!!!!!!!!!!!\n\nVoici le contenu de la globale\n\n");
    printf("TINY = %lu | SMALL = %lu \n\n", TINY, SMALL);
    ok = g_page_one;
    while (ok)
    {

        printf(" page = %lu || SIZE === %lu  ||| busy = %lu ||| sizeof(t_page) = %lu | sizeof(tblock) = %lu\n", (long)ok, ok->size, ok->busy, sizeof(t_page), sizeof(t_block));
        oki = ok->block;
        while (ok->block != NULL)
        {
            if (x==0)
            {
            printf("$$$$$$1er--->Decalage de 16 ou  plus entre ça et le debut --> block = & %lu | strlen(s) == %lu | & %lu (a + b %% 16) | size = %lu | busy= %lu\n", (long)ok->block, strlen(memory_plus(ok->block, sizeof(t_block))), (long)memory_plus(ok->block, sizeof(t_block)), ok->block->size, ok->block->busy);

                x++;
            }else
                printf("--->block = & %lu | strlen(s) == %lu | & %lu (a + b %% 16) | size = %lu | busy= %lu\n", (long)ok->block, strlen(memory_plus(ok->block, sizeof(t_block))), (long)memory_plus(ok->block, sizeof(t_block)), ok->block->size, ok->block->busy);

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
        return TINY;
     //   val = (TINY * 100)+ sizeof(t_page);
    }
    else if (size <= SMALL)
    {
        return SMALL * 10;
        //val = (SMALL * 100)+ sizeof(t_page);

    }
    else
    {
      val = size * 2 + sizeof(t_page);
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

void *place(t_page *page, size_t size, int busy)
{
    size_t ecart;
    t_block *block;
    t_block *prev;
    //printf("\norigin=%lu\n\n", (long)page);

    prev = page->block;
    //printf("prev %lu = %lu\n\n", (long)prev, (long)page->block);
    if ((busy = busy_precision(page, busy)) > 0)
    {
        printf("precision\n\n");
        return (busyness(*page, size, busy));
    }
    ecart = 0;
    int i = 0;
    while (prev && prev->next)
            prev = prev->next;
    //printf("prev %lu = %lu\n\n", (long)prev, (long)page->block);
    printf(" SIZE: %zu\n", page->size);
    printf(" BEFORE: %zu Size asking = %lu\n", page->busy, size + sizeof(t_block));
    block = memory_plus(prev, prev->size);
    block->size = (size + sizeof(t_block));
    block->busy = size;

    block->next = NULL;
    prev->next = block;
    //page->busy += block->size;
    printf("AFTER: %zu\n", page->busy);
    //printf("result %lu + size = %lu + 16 = %lu\n\n", (long)prev, (long)block, (long)memory_plus(block, sizeof(t_block)));

    prev = page->block;
    return (memory_plus(block, sizeof(t_block)));
}

void *not_find(size_t size)
{
    pages++;
    printf("NOTFIND\n");
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
        printf("origin->size(%lu) - origin->busy(%lu) == %lu && size = %lu\n\n", origin->size, origin->busy, origin->size - origin->busy, size);
        if (origin->size >= origin->busy && types_of_var(origin->size, size) && (origin->size - origin->busy >= size + sizeof(t_block)) && (busy = busy_question(origin, size)) != -1)
        {
        printf("2) origin->size(%lu) - origin->busy(%lu) == %lu && size = %lu\n\n", origin->size, origin->busy, origin->size - origin->busy, size);

            printf("Enter\n");

        //    printf("busy = %d origin=%lu\n\n", busy, (long)origin);
          //busy = -1-->no place || 0->size | 1 --> size +t_block
          origin->busy += ((busy == 0) ? size : (size + sizeof(t_block)));
          return (place(origin, size, busy));
        }
        origin = origin->next;
    }
    printf("not enter \n");
    return (not_find(size));
}
/*
int main(int ac, char **av)
{
    int tour = 0;
  pages = 0;
  int ok = pages;
  unsigned int nb = atoi(av[2]);
  char *str1;
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
*/

int main()
{
    int i =-1;
    char *s1, *s2, *s3, *s4, *s5, *s6, *s7, *s8, *s9, *s10
    ,*s11,*s12,*s13,*s14,*s15,*s16,*s17,*s18,*s19,*s20;

    s2 = (char *)my_malloc(sizeof(char) * 5);
    s2 = (s2 ? "abcd\0" : s2);
    printf("s2 = %s\n", s2);

    s4 = (char *)my_malloc(sizeof(char) * 100);
    if (s4){
        while (++i < 99)
            s4[i] = 'a';
        s4[i] = '\0';
        i=-1;
    }
//    printf("s4 = %s || %lu\n", s4, strlen(s4));

    s5 = (char *)my_malloc(sizeof(char) * 300);
    if (s5){
        while (++i < 299)
            s5[i] = 'a';
        s5[i] = '\0';
        i=-1;
    }
    //printf("s5 = %s\n", s5);

    s6 = (char *)my_malloc(sizeof(char) * 1000);
    if (s6){
        while (++i < 999)
            s6[i] = 'a';
        s6[i] = '\0';
        i=-1;
    }
    //printf("s6 = %s\n", s6);

    s7 = (char *)my_malloc(sizeof(char) * 3000);
    if (s7){
        while (++i < 2999)
            s7[i] = 'a';
        s7[i] = '\0';
        i=-1;
    }
    //printf("s7 = %s\n", s7);
    /*
    s8 = (char *)my_malloc(sizeof(char) * 10000);
    if (s8){
        while (++i < 9999)
            s8[i] = 'a';
        s8[i] = '\0';
        i=-1;
    }
    printf("s8 = %s\n", s8);
    */

    s3 = (char *)my_malloc(sizeof(char) * 10);

    if (s3){
        while (++i < 10)
            s3[i] = 'q';
        s3[i] = '\0';
        i=-1;
    }
    printf("s3 = %s\n", s3);

    s9 = (char *)my_malloc(sizeof(char) * 15000);

    if (s9){
        while (++i < 14999)
            s9[i] = 'a';
        s9[i] = '\0';
        i=-1;
    }
  //  printf("s = %s\n", s9);

    s10 = (char *)my_malloc(sizeof(char) * 16000);
    printf("RETOUR S10\n");

    if (s10){
        while (++i < 15999)
            s10[i] = 'a';
        s10[i] = '\0';
        i=-1;
    }
//    printf("s = %s\n", s10);

    s1 = (char *)my_malloc(sizeof(char) *2);
    s1 = (s1 ? "ab\0" : s1);
    printf("s = %s\n\n", s1);

    printf("ADRESSE DE 2 -- > %lu\n\n", (long)s1);
//commencement
//my_realloc(s1, 12);
//my_free(s3);
    printf("\n\n\n\n\n\n\n\n\n\n\n\n");
impress();
printf("\n\n\n");

    show_alloc_mem();
    //my_free(s4);
    //show_alloc_mem();
//impress();
    return 0;
}
