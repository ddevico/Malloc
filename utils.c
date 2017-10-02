/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddevico <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 15:15:20 by ddevico           #+#    #+#             */
/*   Updated: 2017/10/02 13:44:29 by ddevico          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/malloc.h"

void		impress(void)
{
	int		x;
	t_page	*ok;
	t_block	*oki;
	printf("!!!!!!!!!!!!!!!!!!!!\n\nVoici le contenu de la globale\n\n");
	printf("TINY = %lu | SMALL = %lu \n\n", (unsigned long)TINY, (unsigned long)SMALL);
	ok = g_page_one;
	x = 0;
	while (ok)
	{
		printf("page = %lu || SIZE === %lu  ||| busy = %lu ||| sizeof(t_page) = %lu | sizeof(tblock) = %lu\n", (long)ok, ok->size, ok->busy,
		sizeof(t_page), sizeof(t_block));
		oki = ok->block;
		while (ok->block != NULL)
		{
			if (x == 0)
			{
				printf("$$$$$$1er--->Decalage de 16 ou  plus entre ça et le debut --> block = & %lu | strlen(s) == %lu | & %lu (a + b %% 16) | size = %lu | busy= %lu\n", (long)ok->block,
				strlen(memory_plus(ok->block, sizeof(t_block))),
				(long)memory_plus(ok->block, sizeof(t_block)), ok->block->size,
				ok->block->busy);
				x++;
			}
			else
				printf("--->block = & %lu | strlen(s) == %lu | & %lu (a + b %% 16) | size = %lu | busy= %lu\n", (long)ok->block,
				strlen(memory_plus(ok->block, sizeof(t_block))),
				(long)memory_plus(ok->block, sizeof(t_block)), ok->block->size,
				ok->block->busy);
			if (!ok->block->next)
				break ;
			ok->block = ok->block->next;
		}
		ok->block = oki;
		x = 0;
		ok = ok->next;
	}
	printf("\n\n!!!!!!!!!!!!!!!!!!!!\n\n");
}

int			types_of_var(size_t page, size_t size)
{
	size = type_of_size(size);
	if (page == size && size != ((size / (size_t)getpagesize()) + 10) * getpagesize())
		return (1);
	return (0);
}

void		*memory_plus(void *addr, size_t inc)
{
	size_t d;

	d = 0;
	
	while (d < inc)
	{
		addr++;
		d++;
	}
	return (addr);
}

size_t		type_of_size(size_t size)
{
	if (size + sizeof(t_block) <= TINY)
		return (TINY * 100);
	else if (size + sizeof(t_block) <= SMALL)
		return (SMALL * 100);
	else
		return ((size / (size_t)getpagesize()) + 10) * getpagesize();
}

void		*busyness(t_page page, size_t size, int busy)
{
	t_block	*block;

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
