/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddevico <ddevico@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 15:56:40 by ddevico           #+#    #+#             */
/*   Updated: 2017/09/29 11:57:07 by davydevico       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/malloc.h"

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

static void			put_pointer(void *ptr)
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
	ft_putstr(", ");
	ft_putstr(memory_plus(page->block, sizeof(t_block)));
	ft_putstr(" | var busy memory = ");
	ft_putnbr(page->block->busy);
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
		if (page->size <= (TINY * 100))
			n = n + print_mem("TINY: ", page);
		else if (page->size <= (SMALL * 100))
			n = n + print_mem("SMALL: ", page);
		else
			n = n + print_mem("LARGE: ", page);
		page->block = block;
		page = page->next;
	}
	ft_putstr("Total: ");
	ft_putnbr(n);
}
