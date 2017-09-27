/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddevico <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 15:56:40 by ddevico           #+#    #+#             */
/*   Updated: 2017/09/26 17:23:39 by ddevico          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/malloc.h"

static void				print_mem(t_page *page)
{
	printf("0x%lX - 0x%lX : %lu octets, %s | var busy memory = %lu\n",
			(unsigned long)page->block,
			(unsigned long)page->block + page->block->size,
			page->block->size, memory_plus(page->block, sizeof(t_block)),
			page->block->busy);
	page->block = page->block->next;
}

void				show_alloc_mem(void)
{
	t_page			*page;
	t_block			*block;
	unsigned long	n;

	page = g_page_one;
	n = 0;
	if (page == NULL)
		printf("No allocation\n");
	while (page)
	{
		block = page->block;
		if (page->size <= (TINY * 100))
			printf("TINY: 0x%lX\n", (unsigned long)page);
		else if (page->size <= (SMALL * 100))
			printf("SMALL: 0x%lX\n", (unsigned long)page);
		else
			printf("LARGE: 0x%lX\n", (unsigned long)page);
		while (page->block != NULL)
		{
			n += page->block->size;
			print_mem(page);
		}
		page->block = block;
		page = page->next;
	}
	printf("Total: %lu\n", n);
}
