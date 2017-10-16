/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_calling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tktorza <tktorza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 13:36:57 by tktorza           #+#    #+#             */
/*   Updated: 2017/10/16 12:53:28 by ddevico          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void		*malloc(size_t size)
{
	void	*ptr;

	malloc_init();
	ptr = exec_malloc(size);
	return (ptr);
}

void		free(void *ptr)
{
	malloc_init();
	exec_free(ptr);
}

void		*realloc(void *ptr, size_t size)
{
	void	*ret;

	malloc_init();
	ret = exec_realloc(ptr, size);
	return (ret);
}

void		*update_maillon(t_page *page, t_block *one, void *ptr, size_t size)
{
	if (!one->next && page->size - page->busy >= size)
	{
		one->size = size + sizeof(t_block);
		page->busy += one->size;
	}
	one->busy = size;
	return (ptr);
}
