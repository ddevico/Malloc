#include "includes/malloc.h"

void show_alloc_mem()
{
  t_page *page;
  t_block *block;
  unsigned long n;

  n = 0;
  page = g_page_one;
  if (page == NULL)
    printf("No allocation\n");
  //printf("%zu\n", page->size);
  while (page)
  {
    block = page->block;
    if (page->size == (TINY))
      printf("TINY: 0x%lX\n", (unsigned long)page);
    else if (page->size == (SMALL))
      printf("SMALL: 0x%lX\n", (unsigned long)page);
    else
      printf("LARGE: 0x%lX\n", (unsigned long)page);
    while (page->block != NULL)
    {
      n += page->block->size;
      printf("0x%lX - 0x%lX : %lu octets\n",
  	       (unsigned long)page->block,
  	       (unsigned long)page->block + page->block->size,
  	       page->block->size);
      page->block = page->block->next;
    }
    page->block = block;
    page = page->next;
  }
  printf("Total: %lu\n", n);
}
