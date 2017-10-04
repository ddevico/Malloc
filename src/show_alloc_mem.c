/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tktorza <tktorza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 12:05:31 by tktorza           #+#    #+#             */
/*   Updated: 2017/10/04 09:42:06 by davydevico       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static void			put_hexa(unsigned long h)
{
	const char		*hex = "0123456789abcdef";

	if (h >= 16)
	{
		put_hexa(h / 16);
		put_hexa(h % 16);
	}
	else
		ft_putchar(hex[h]);
}

void				put_pointer(void *ptr)
{
	ft_putstr("0x");
	put_hexa((unsigned long)ptr);
}

static void			print_mem_2(t_page *page)
{
	put_pointer(page->block);
	ft_putstr(" - ");
	put_pointer((void*)page->block + page->block->size);
	ft_putstr(" : ");
	ft_putnbr(page->block->size);
	ft_putstr(" octets");
	ft_putendl("");
	page->block = page->block->next;
}

static unsigned int	print_mem(char *str, t_page *page)
{
	unsigned int	n;

	n = 0;
	ft_putstr(str);
	put_pointer(page);
	ft_putstr("\n");
	while (page->block != NULL)
	{
		n += page->block->size;
		print_mem_2(page);
	}
	return (n);
}

void				show_alloc_mem(void)
{
	t_page			*page;
	t_block			*block;
	unsigned long	n;

	page = g_page_one;
	n = 0;
	while (page)
	{
		block = page->block;
		if (page->size <= (TINY * 100) && page->block && page->block->size <=
				TINY)
			n = n + print_mem("TINY: ", page);
		else if (page->size <= (SMALL * 100) && page->block && page->block->size
				<= SMALL)
			n = n + print_mem("SMALL: ", page);
		else
			n = n + print_mem("LARGE: ", page);
		page->block = block;
		page = page->next;
	}
	ft_putstr("Total: ");
	ft_putnbr(n);
	ft_putendl("");
}
