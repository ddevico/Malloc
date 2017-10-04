/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tktorza <tktorza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 12:05:40 by tktorza           #+#    #+#             */
/*   Updated: 2017/10/04 09:42:11 by davydevico       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

int			types_of_var(size_t page, size_t size)
{
	size = type_of_size(size);
	if (page == size && size != ((size / (size_t)getpagesize()) + 10) *
			getpagesize())
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
		return (((size / (size_t)getpagesize()) + 10) * getpagesize());
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

int			busy_precision(t_page *origin, size_t size)
{
	t_block	*prev;
	int		index;

	index = 0;
	prev = origin->block;
	while (prev)
	{
		index++;
		if (prev->busy > 0 && ((prev->size - prev->busy - sizeof(t_block)) >
			sizeof(t_block) + size))
			return (index);
		if (prev->busy == 0 && prev->size - sizeof(t_block) >= size)
			return (index);
		prev = prev->next;
	}
	return (0);
}
