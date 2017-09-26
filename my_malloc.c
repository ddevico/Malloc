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
        return TINY * 100;
     //   val = (TINY * 100)+ sizeof(t_page);
    }
    else if (size <= SMALL)
    {
        return SMALL * 100;
        //val = (SMALL * 100)+ sizeof(t_page);
    }
    else
    {
      //val = size * 100 + sizeof(t_page);
      val = LARGE * 100 + sizeof(t_page);
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
        printf("buzyyy placeeeeee %lu\n", busy);
        return (busyness(*page, size, busy));
    }
    ecart = 0;
    int i = 0;
    while (prev && prev->next)
            prev = prev->next;
    //printf("prev %lu = %lu\n\n", (long)prev, (long)page->block);
    //printf(" SIZE: %zu\n", page->size);
    //printf(" BEFORE: %zu Size asking = %lu\n", page->busy, size + sizeof(t_block));
    block = memory_plus(prev, prev->size);
    block->size = (size + sizeof(t_block));
    block->busy = size;

    block->next = NULL;
    prev->next = block;
    //page->busy += block->size;
    //printf("AFTER: %zu\n", page->busy);
    ////printf("result %lu + size = %lu + 16 = %lu\n\n", (long)prev, (long)block, (long)memory_plus(block, sizeof(t_block)));

    prev = page->block;
    return (memory_plus(block, sizeof(t_block)));
}

void *not_find(size_t size)
{
    pages++;
    //printf("NOTFIND\n");
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
        //printf("origin->size(%lu) - origin->busy(%lu) == %lu && size = %lu\n\n", origin->size, origin->busy, origin->size - origin->busy, size);
        //regarder 3eme condition
        if (origin->size >= origin->busy && types_of_var(origin->size, size) && (origin->size - origin->busy >= size + sizeof(t_block)) && (busy = busy_question(origin, size)) != -1)
        {
        //printf("2) origin->size(%lu) - origin->busy(%lu) == %lu && size = %lu\n\n", origin->size, origin->busy, origin->size - origin->busy, size);
            //printf("Enter\n");
          origin->busy += ((busy == 0) ? size : (size + sizeof(t_block)));
          //printf("origin buzy nouveauuuuuuuu%lu\n", (long)origin->busy);
          return (place(origin, size, busy));
        }
        origin = origin->next;
    }
    //printf("not enter \n");
    return (not_find(size));
}

void    *my_calloc(size_t num, size_t nsize)
{
    size_t	size;
	  void	*ret;
    char			*str;
  	unsigned char	car;
  	size_t			i;
    i = 0;

    if (!num || !nsize)
		  return (NULL);
    size = num * nsize;
    if (nsize != size / num)
		  return (NULL);
    ret = my_malloc(size);
    car = (unsigned char)0;
  	str = (char *)ret;
    if (!ret)
      return (NULL);
    ft_memset(ret, 0, size);
  	/*while (i < size)
  	{
  		str[i] = car;
  		i++;
  	}*/
    //printf("%lu\n", (unsigned long)ret);
    return (ret);
}

int main()
{
    int i =-1;
    char *s1, *s2, *s3, *s4, *s5, *s6, *s7, *s8, *s9, *s10,*s11,*s12,*s13,*s14,*s15,*s16,*s17,*s18,*s19,*s20;

    s1 = (char *)my_malloc(sizeof(char) * 21);
    if (s1){
        while (++i < 10)
            s1[i] = 'a';
        s1[i] = '\0';
        i=-1;
    }

    s2 = (char *)my_malloc(sizeof(char) * 500);
    if (s2){
        while (++i < 10)
            s2[i] = 'b';
        s2[i] = '\0';
        i=-1;
    }

    s3 = (char *)my_malloc(sizeof(char) * 200);
    if (s3){
        while (++i < 10)
            s3[i] = 'c';
        s3[i] = '\0';
        i=-1;
    }

    s4 = (char *)my_malloc(sizeof(char) * 10);
    if (s4){
        while (++i < 10)
            s4[i] = 'd';
        s4[i] = '\0';
        i=-1;
    }

    s5 = (char *)my_malloc(sizeof(char) * 11);
    if (s5){
        while (++i < 10)
            s5[i] = 'e';
        s5[i] = '\0';
        i=-1;
    }

    s6 = (char *)my_malloc(sizeof(char) * 400);
    if (s6){
        while (++i < 10)
            s6[i] = 'f';
        s6[i] = '\0';
        i=-1;
    }

    s7 = (char *)my_malloc(sizeof(char) * 400);
    if (s7){
        while (++i < 10)
            s7[i] = 'g';
        s7[i] = '\0';
        i=-1;
    }

    s8 = (char *)my_malloc(sizeof(char) * 1000);
    if (s8){
        while (++i < 10)
            s8[i] = 'h';
        s8[i] = '\0';
        i=-1;
    }
    s9 = (char *)my_malloc(sizeof(char) * 300);
    if (s9){
        while (++i < 10)
            s9[i] = 'i';
        s9[i] = '\0';
        i=-1;
    }

    s10 = (char *)my_malloc(sizeof(char) * 9000);
    if (s10){
        while (++i < 10)
            s10[i] = 'j';
        s10[i] = '\0';
        i=-1;
    }



    show_alloc_mem();
    /*impress();
    printf("\n\n\n\n\n\n\n");*/my_free(s4);my_free(s3);

    show_alloc_mem();
    s11 = (char *)my_malloc(sizeof(char) * 205);
    if (s11){
        while (++i < 100)
            s11[i] = '1';
        s11[i] = '\0';
        i=-1;
    }

    printf("\n\n\nnew\n\n\n");
    show_alloc_mem();

    /*my_free(s1);

    show_alloc_mem();
    printf("asking::: %lu\n", sizeof(t_block));

    s20 = (char *)my_malloc(sizeof(char) * 20);
    printf("asking::: %lu\n", sizeof(char) * 12);

    show_alloc_mem();
    if (s20){
        while (++i < 10)
            s20[i] = 'p';
        s20[i] = '\0';
        i=-1;
    }
    my_free(s5);
    printf("\n\n\nnew\n\n\n");
    show_alloc_mem();*/

    my_free(s1);
    show_alloc_mem();
    my_free(s2);
    show_alloc_mem();
    my_free(s3);
    show_alloc_mem();
    my_free(s4);
    show_alloc_mem();
    my_free(s5);
    show_alloc_mem();
    my_free(s6);
    show_alloc_mem();
    my_free(s7);
    show_alloc_mem();
    my_free(s8);
    show_alloc_mem();
    my_free(s9);
    show_alloc_mem();
    my_free(s10);
    show_alloc_mem();
    my_free(s11);
    show_alloc_mem();
    my_free(s20);
    show_alloc_mem();
 i =-1;

    s1 = (char *)my_malloc(sizeof(char) * 21);
    if (s1){
        while (++i < 10)
            s1[i] = 'a';
        s1[i] = '\0';
        i=-1;
    }

    s2 = (char *)my_malloc(sizeof(char) * 500);
    if (s2){
        while (++i < 10)
            s2[i] = 'b';
        s2[i] = '\0';
        i=-1;
    }

    s3 = (char *)my_malloc(sizeof(char) * 200);
    if (s3){
        while (++i < 10)
            s3[i] = 'c';
        s3[i] = '\0';
        i=-1;
    }

    s4 = (char *)my_malloc(sizeof(char) * 10);
    if (s4){
        while (++i < 10)
            s4[i] = 'd';
        s4[i] = '\0';
        i=-1;
    }

    s5 = (char *)my_malloc(sizeof(char) * 11);
    if (s5){
        while (++i < 10)
            s5[i] = 'e';
        s5[i] = '\0';
        i=-1;
    }

    s6 = (char *)my_malloc(sizeof(char) * 400);
    if (s6){
        while (++i < 10)
            s6[i] = 'f';
        s6[i] = '\0';
        i=-1;
    }

    s7 = (char *)my_malloc(sizeof(char) * 400);
    if (s7){
        while (++i < 10)
            s7[i] = 'g';
        s7[i] = '\0';
        i=-1;
    }

    s8 = (char *)my_malloc(sizeof(char) * 1000);
    if (s8){
        while (++i < 10)
            s8[i] = 'h';
        s8[i] = '\0';
        i=-1;
    }
    s9 = (char *)my_malloc(sizeof(char) * 300);
    if (s9){
        while (++i < 10)
            s9[i] = 'i';
        s9[i] = '\0';
        i=-1;
    }

    s10 = (char *)my_malloc(sizeof(char) * 9000);
    if (s10){
        while (++i < 10)
            s10[i] = 'j';
        s10[i] = '\0';
        i=-1;
    }



    show_alloc_mem();
    /*impress();
    printf("\n\n\n\n\n\n\n");*/my_free(s4);my_free(s3);

    show_alloc_mem();
    s11 = (char *)my_malloc(sizeof(char) * 205);
    if (s11){
        while (++i < 100)
            s11[i] = '1';
        s11[i] = '\0';
        i=-1;
    }

    printf("\n\n\nnew\n\n\n");
    show_alloc_mem();

    /*my_free(s1);

    show_alloc_mem();
    printf("asking::: %lu\n", sizeof(t_block));

    s20 = (char *)my_malloc(sizeof(char) * 20);
    printf("asking::: %lu\n", sizeof(char) * 12);

    show_alloc_mem();
    if (s20){
        while (++i < 10)
            s20[i] = 'p';
        s20[i] = '\0';
        i=-1;
    }
    my_free(s5);
    printf("\n\n\nnew\n\n\n");
    show_alloc_mem();*/

    printf("\n\n\nnew\n\n\n");
    s12 = (char *)my_calloc(300, sizeof(char));
    if (s12){
        while (++i < 5)
            s12[i] = '2';
        s12[i] = '\0';
        i=-1;
    }
    show_alloc_mem();

    return 0;
}
