#include "includes/malloc.h"

static void			put_hexa_dump(unsigned long h)
{
	const char		*hex = "0123456789abcdef";
	static int i;

	if (h >= 16)
	{
		put_hexa_dump(h / 16);
		put_hexa_dump(h % 16);
	}
	else
	{
		ft_putchar(hex[h]);
		i++;
		if (i == 2)
		{
			ft_putstr(" ");
			i = 0;
		}
	}
}

static void      print_dump(t_page *page, unsigned int i)
{
  while (page->block != NULL)
  {
    while (i < page->block->size)
    {
        put_pointer(memory_plus(page->block, i));
        ft_putstr(": ");
        put_hexa_dump((unsigned long)memory_plus(page->block, i));
				ft_putchar(' ');
        ft_putchar(((char *)memory_plus(page->block, i))[0]);
        ft_putchar('\n');
        i++;
    }
    page->block = page->block->next;
  }
}

static void       test_type(t_page *page, int type, unsigned int i)
{
  if (type == 0)
  {
    if (page->size == (TINY * 100) && page->block)
      print_dump(page, i);
  }
  else if (type == 1)
  {
    if (page->size == (SMALL * 100) && page->block)
      print_dump(page, i);
  }
  else if (page->size > (SMALL * 100) && page->block)
    print_dump(page, i);
}

void			dump(int type)
{
    t_page			*page;
  	t_block			*block;
    unsigned int  i;

  	page = g_page_one;
  	while (page)
  	{
      i = sizeof(t_block);
      block = page->block;
      if (type == 0 || type == 1 || type == 2)
        test_type(page, type, i);
      else if (type == 3)
          print_dump(page, i);
      else
        ft_putstr("Error number for dump");
  		page->block = block;
  		page = page->next;
  	}
}
