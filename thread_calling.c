/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_calling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tktorza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 13:36:57 by tktorza           #+#    #+#             */
/*   Updated: 2017/10/03 16:09:55 by ddevico          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/malloc.h"

void		*malloc(size_t size)
{
	void	*ptr;

	malloc_init();
	//pthread_mutex_lock(&g_mutex);
	ptr = exec_malloc(size);
	pthread_mutex_unlock(&g_mutex);
	return (ptr);
}

void		free(void *ptr)
{
	malloc_init();
	//pthread_mutex_lock(&g_mutex);
	exec_free(ptr);
	pthread_mutex_unlock(&g_mutex);
}

void		*realloc(void *ptr, size_t size)
{
	void	*ret;

	malloc_init();
	//pthread_mutex_lock(&g_mutex);
	ret = exec_realloc(ptr, size);
	pthread_mutex_unlock(&g_mutex);
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
