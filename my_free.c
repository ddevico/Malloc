/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddevico <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 15:15:20 by ddevico           #+#    #+#             */
/*   Updated: 2017/09/26 16:17:39 by ddevico          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/malloc.h"

int					busy_precision(t_page *origin, size_t size)
{
	t_block			*prev;
	int				index;

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

int					busy_question(t_page *origin, size_t size)
{
	t_block			*prev;
	int				pull;
	int				index;

	index = 0;
	pull = 0;
	prev = origin->block;
	while (prev)
	{
		index++;
		if (prev->busy > 0 && ((prev->size - prev->busy - sizeof(t_block)) >
			sizeof(t_block) + size))
			return (1);
		else if (prev->busy == 0 && prev->size - sizeof(t_block) >= size)
			return (0);
		else
			pull += (prev->size - sizeof(t_block));
		prev = prev->next;
	}
	return ((origin->size - (origin->busy + pull) >= size) ? 1 : -1);
}

t_page				*delete_page(t_page *origin, t_page *page)
{
	while (origin->next && (void *)(origin->next) != (void*)page)
		origin = origin->next;
	if (origin && origin->next)
	{
		origin->next = (origin->next)->next;
		munmap((void*)page, page->size);
		return (origin->next);
	}
	return (NULL);
}

void				try_to_delete_page(void)
{
	t_page			*first;
	t_block			*begin;
	int				busy;

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

void				free(void *ptr)
{
	t_page			*first;
	t_block			*one;
	t_block			*begin;
	size_t			plus;

	first = g_page_one;
	while (first)
	{
		one = first->block;
		while (first->block != NULL)
		{
			if (ptr == memory_plus(first->block, sizeof(t_block)))
			{
				ft_bzero(memory_plus(first->block, sizeof(t_block)),
						first->block->busy);
				first->block->busy = 0;
				begin = first->block;
				plus = begin->size;
				if (begin->next && (begin->next)->busy == 0)
				{
					while ((begin->next) && (begin->next)->busy == 0)
					{
						plus += (begin->next)->size;
						begin = begin->next;
					}
					first->block->size = plus;
					first->block->next = begin->next;
					ft_bzero(memory_plus(first->block, sizeof(t_block)),
							first->block->size - sizeof(t_block));
				}
				else if (!begin->next)
				{
					first->block = one;
					while ((void *)((first->block)->next) &&
							(void *)((first->block)->next) != (void *)begin)
						first->block = first->block->next;
					first->block->next = NULL;
				}
				first->block = one;
				return (try_to_delete_page());
			}
			first->block = first->block->next;
		}
		first->block = one;
		first = first->next;
	}
}
