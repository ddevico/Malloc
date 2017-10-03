/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddevico <ddevico@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 15:56:40 by ddevico           #+#    #+#             */
/*   Updated: 2017/10/02 13:40:21 by ddevico          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/malloc.h"

void		*ft_memcpy_realloc(void *dst, const void *src, size_t n)
{
	size_t		i;
	char		*a;
	const char	*b;

	if (src == NULL || dst == NULL)
		return (NULL);
	i = 0;
	a = (char *)dst;
	b = (const char *)src;
	while (i < n)
	{
		if (b[i])
			a[i] = b[i];
		i++;
	}
	return (dst);
}

static int	realloc_if(t_block *one, size_t size)
{
	one->size += (one->next)->size;
	one->busy = size;
	one->next = (one->next)->next;
	return (0);
}

static void	*try_to_realloc(t_block *one, void *ptr, size_t size)
{
	void		*next;

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
		ft_memcpy_realloc(next, ptr, ((size < one->busy) ? size : one->busy));
		free(ptr);
		return (next);
	}
}

void		*to_realloc(t_value *val, void *ptr, t_page *first, t_block *one)
{
	if (val->size == 0)
	{
		free(ptr);
		return (NULL);
	}
	ptr = try_to_realloc(first->block, ptr, val->size);
	if (val->y != 0)
		first->block = one;
	return ((ptr == NULL) ? malloc(val->size) : ptr);
}

void		*realloc(void *ptr, size_t size)
{
	t_page		*first;
	t_block		*one;
	t_value		val;

	val.size = size;
	first = g_page_one;
	while (first)
	{
		one = first->block;
		val.y = 0;
		while (first->block != NULL)
		{
			if (ptr && ptr == memory_plus(first->block, sizeof(t_block)))
				return (to_realloc(val, ptr, first, one));
			first->block = first->block->next;
			val.y++;
		}
		first->block = one;
		first = first->next;
	}
	first = g_page_one;
	return ((ptr == NULL) ? malloc(size) : NULL);
}
