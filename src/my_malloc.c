/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tktorza <tktorza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 12:05:00 by tktorza           #+#    #+#             */
/*   Updated: 2017/10/16 12:52:23 by ddevico          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static void			*place(t_page *page, size_t size, int busy)
{
	size_t			ecart;
	t_block			*block;
	t_block			*prev;
	int				i;

	i = 0;
	prev = page->block;
	if ((busy = busy_precision(page, size)) > 0)
		return (busyness(*page, size, busy));
	ecart = 0;
	while (prev && prev->next)
		prev = prev->next;
	block = memory_plus(prev, prev->size);
	block->size = (size + sizeof(t_block));
	block->busy = size;
	block->next = NULL;
	prev->next = block;
	prev = page->block;
	return (memory_plus(block, sizeof(t_block)));
}

static void			*not_find(size_t size)
{
	t_page			*origin;
	t_page			*add;
	t_block			*block;

	origin = g_page_one;
	add = mmap(NULL, type_of_size(size), PROT_WRITE | PROT_READ, MAP_ANON |
			MAP_PRIVATE, -1, 0);
	if (add == MAP_FAILED)
		return (NULL);
	add->busy = size + sizeof(t_page) + sizeof(t_block);
	add->size = type_of_size(size);
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

void				*exec_malloc(size_t size)
{
	int				busy;
	t_page			*origin;

	busy = 0;
	origin = g_page_one;
	while (origin)
	{
		if (origin->size >= origin->busy && types_of_var(origin->size, size) &&
		(origin->size - origin->busy >= size + sizeof(t_block)) &&
		(busy = busy_question(origin, size)) != -1)
		{
			origin->busy += ((busy == 0) ? size : (size + sizeof(t_block)));
			return (place(origin, size, busy));
		}
		origin = origin->next;
	}
	return (not_find(size));
}

void				malloc_init(void)
{
	static int		first = 0;

	if (first == 0)
	{
		g_page_one = NULL;
		first = 1;
	}
}
