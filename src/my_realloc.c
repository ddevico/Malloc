/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tktorza <tktorza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 12:05:14 by tktorza           #+#    #+#             */
/*   Updated: 2017/10/04 09:42:04 by davydevico       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static void		*ft_memcpy_realloc(void *dst, const void *src, size_t n)
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

static int		realloc_if(t_block *one, size_t size)
{
	one->size += (one->next)->size;
	one->busy = size;
	one->next = (one->next)->next;
	return (0);
}

static void		*try_to_realloc(t_page *page, t_block *one, void *ptr,
				size_t size)
{
	void		*next;

	if (one->size - sizeof(t_block) >= size || (!one->next && page->size -
				page->busy >= size))
		return (update_maillon(page, one, ptr, size));
	else if (one->next && (one->next)->busy == 0 && one->size +
			(one->next)->size - sizeof(t_block) >= size)
	{
		realloc_if(one, size);
		return (ptr);
	}
	else
	{
		next = exec_malloc(size);
		ft_memcpy_realloc(next, ptr, ((size < one->busy) ? size : one->busy));
		exec_free(ptr);
		return (next);
	}
}

static void		*to_realloc(t_value val, void *ptr, t_page *first, t_block *one)
{
	if (val.size == 0)
	{
		exec_free(ptr);
		return (exec_malloc(1));
	}
	ptr = try_to_realloc(first, first->block, ptr, val.size);
	if (val.y != 0)
		first->block = one;
	return ((ptr == NULL) ? exec_malloc(val.size) : ptr);
}

void			*exec_realloc(void *ptr, size_t size)
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
	return ((ptr == NULL) ? exec_malloc(size) : NULL);
}
