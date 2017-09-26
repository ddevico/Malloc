#include "includes/malloc.h"

int     busy_precision(t_page *origin, size_t size)
{
    t_block *prev;
    int     index;

    index = 0;
    prev = origin->block;
    while (prev)
    {
        index++;
            printf("++++++++++++++++++++++++++++++++++++++ cas 1 size(%lu) busy(%lu) == %lu - %lu > %lu \n\n", prev->size, prev->busy, (prev->size - prev->busy),  sizeof(t_block), sizeof(t_block) + size);
            //regarder la comparaison des size_t
        if (prev->busy > 0 && ((prev->size - prev->busy - sizeof(t_block)) > sizeof(t_block) + size))
        {
            printf("++++++++++++++++++++++++++++++++++++++ cas 1 == %lu > %lu \n\n", (prev->size - prev->busy - sizeof(t_block)), sizeof(t_block) + size);
            return (index);
        }
        if (prev->busy == 0 && prev->size - sizeof(t_block) >= size)
            {
                printf("------------------------------------------>cas 2 == %lu >= %lu\n\n", prev->size - sizeof(t_block), size);
                return (index);
            }
        prev = prev->next;
    }

    return (0);
}

int     busy_question(t_page *origin, size_t size)
{
    t_block *prev;
    int     pull;
    int     index;

    index = 0;
    pull = 0;
    prev = origin->block;
    while (prev)
    {
        index++;
        //regarder la comparaison des size_t
        if (prev->busy > 0 && ((prev->size - prev->busy - sizeof(t_block)) > sizeof(t_block) + size))
            {
                printf("----------------------------____-------->busy_question 1\n\n");
                return (1);
            }
        else if (prev->busy == 0 && prev->size - sizeof(t_block) >= size)
        {
            printf("----------------------------____-------->busy_question 2\n\n");            
            return (0);
            //busy = taille de l'element sans le block
            //busy peut etre >= a 1, il y a plusieurs blocks de place
            //busy ==1 lorsque free puis malloc de cette zone
            //donc ancien block precede nouvelle var
            //mtn block var nouveau block nouvelle var avec ce block si ne rempli pas completement
            // l'espace sera busy en 2 ca veut dire que place pour eventuel autre block
            //mais checker si place pour autre block deja
            //--> block->size - block->busy - sizeof(t_block) >= sizeof(t_block) + size
            //dans ce cas creer nouveau block et l'inserer entre
        }
        else
            pull += (prev->size - sizeof(t_block));
        prev = prev->next;
    }

    return ((origin->size - (origin->busy + pull) >= size) ? 1 : -1);
}

t_page   *delete_page(t_page *origin, t_page *page)
{
    while (origin->next && (void *)(origin->next) != (void*)page)
        origin = origin->next;
    if (origin && origin->next)
    {
        origin->next = (origin->next)->next;
        //!!!!!!!!!!!!!!! bzero((void*)page, page->size);
        munmap((void*)page, page->size);
        return (origin->next);
    }
    return NULL;
}

void    try_to_delete_page(void)
{
    t_page *first;
    t_block *begin;
    int busy;

    first = g_page_one;
    while (g_page_one)
    {
        busy = 0;
        begin = g_page_one->block;
        while (g_page_one->block)
        {
            busy += g_page_one->block->busy;
            g_page_one->block = g_page_one->block->next;
        }
        if (busy == 0 && (void *)g_page_one == (void *)first)
        {
            first = g_page_one->next;
            munmap((void*)g_page_one, g_page_one->size);
            g_page_one = first;
        }
        else if (busy == 0)
            g_page_one = delete_page(first, g_page_one);
        else
        {
            g_page_one->block = begin;
            g_page_one = g_page_one->next;
        }
    }
    g_page_one = first;
}

void my_free(void *ptr)
{
    static size_t tour = 0;
    //tous les n tours
    //checker si page vide --> supprimer tout le maillon avec bzero
    printf("\n\nFREE\n\n");
    t_page *first;
    t_block *one;
    t_block *begin;
    size_t  plus;
    //printf("$$$$$$$$$$$$this is it--> & %lu\n", (long)ptr);
    if (tour % 10 == 0)
        try_to_delete_page();

    first = g_page_one;
    while (first)
    {
        one = first->block;
        while (first->block != NULL)
        {
          printf("%lu ==> %lu\n", (long)ptr, (long)memory_plus(first->block, sizeof(t_block)));
          if (ptr == memory_plus(first->block, sizeof(t_block)))
           {
               printf("--->block = & %lu | str = '%s' & %lu (a + b %% 16) | size = %lu\n", (long)first->block, (char *)memory_plus(first->block, sizeof(t_block)), (long)memory_plus(first->block, sizeof(t_block)), first->block->size);
              ft_bzero(memory_plus(first->block, sizeof(t_block)), first->block->busy);
               first->block->busy = 0;
               begin = first->block;
               plus = begin->size;
               if (begin->next && (begin->next)->busy == 0)
               {
                  printf("n'est pas cense etre laaaa\n\n");
                   while((begin->next) && (begin->next)->busy == 0)
                   {
                    plus += (begin->next)->size;
                    begin = begin->next;
                   }
                   first->block->size = plus;
                   first->block->next = begin->next;
                    ft_bzero(memory_plus(first->block, sizeof(t_block)), first->block->size - sizeof(t_block));
               }
               else if (!begin->next)
               {
                printf("dernier maillon frero || disparition du maillon\n\n");      
                   first->block = one;
                   while ((void *)((first->block)->next) && (void *)((first->block)->next) != (void *)begin)
                        first->block = first->block->next;
                    first->block->next = NULL;
            }
               //pq pas opti en verifiant si le bloc qui suit n'est pas vide pour en faire
             //un gros (en recurence)
               first->block = one;
               return;
           }
            first->block = first->block->next;
        }
        first->block = one;
        first = first->next;
    }
    
    printf("\n\n!!!!!!!!!!!!!!!!!!!!\n\n");
}
