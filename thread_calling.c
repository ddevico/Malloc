/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_calling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tktorza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 13:36:57 by tktorza           #+#    #+#             */
/*   Updated: 2017/10/03 13:36:58 by tktorza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/malloc.h"

void		*malloc(size_t size)
{
	void 			*ptr;
	
	malloc_init();
	pthread_mutex_lock(&g_mutex);
	ptr = exec_malloc(size);
	pthread_mutex_unlock(&g_mutex);
	return (ptr);
}

void		free(void *ptr)
{
	malloc_init();
	pthread_mutex_lock(&g_mutex);
	exec_free(ptr);
	pthread_mutex_unlock(&g_mutex);
}


void		*realloc(void *ptr, size_t size)
{
	void *ret;
	
	malloc_init();
	pthread_mutex_lock(&g_mutex);
	ret = exec_realloc(ptr, size);
    pthread_mutex_unlock(&g_mutex);
    return (ret);
}