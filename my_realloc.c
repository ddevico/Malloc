/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddevico <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 15:56:40 by ddevico           #+#    #+#             */
/*   Updated: 2017/09/26 16:00:50 by ddevico          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/malloc.h"

static int	realloc_if(t_block *one, size_t size)
{
	one->size += (one->next)->size;
	one->busy = size;
	one->next = (one->next)->next;
	return (0);
}

static void	*try_to_realloc(t_block *one, void *ptr, size_t size)
{
	void	*next;

	if (size == 0 && ptr != NULL)
	{
		free(ptr);
		return (malloc(1));
	}
	if (one->size - sizeof(t_block) >= size)
	{
		one->busy = size;
		return (ptr);
	}
	else if (one->next && (one->next)->busy == 0 && one->size +
			(one->next)->size - sizeof(t_block) >= size)
	{
		realloc_if(one, size);
		return (ptr);
	}
	else
	{
		next = malloc(size);
		ft_memcpy(next, ptr, ((size < one->busy) ? size : one->busy));
		free(ptr);
		return (next);
	}
}

void		*realloc(void *ptr, size_t size)
{
	t_page	*first;
	t_block	*one;

	first = g_page_one;
	while (first)
	{
		one = first->block;
		while (first->block != NULL)
		{
			if (ptr && ptr == memory_plus(first->block, sizeof(t_block)))
			{
				ptr = try_to_realloc(first->block, ptr, size);
				first->block = one;
				break ;
			}
			first->block = first->block->next;
		}
		first->block = one;
		first = first->next;
	}
    first = g_page_one;
    printf("OKOKOKOKOKOKOK\n\n\n");
    show_alloc_mem();
	return ((ptr == NULL) ? malloc(size) : ptr);
}
