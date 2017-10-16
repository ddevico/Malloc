/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tktorza <tktorza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 12:04:39 by tktorza           #+#    #+#             */
/*   Updated: 2017/10/04 09:42:17 by davydevico       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

int			busy_increment(int busy)
{
	while (g_page_one->block)
	{
		busy += g_page_one->block->busy;
		g_page_one->block = g_page_one->block->next;
	}
	return (busy);
}

void		*exec_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	new_size;

	if (!nmemb || !size)
		return (NULL);
	new_size = nmemb * size;
	if (size != new_size / nmemb)
		return (NULL);
	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	if (ptr)
		ft_bzero(ptr, nmemb * size);
	return (ptr);
}

void		*calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	malloc_init();
	ptr = exec_calloc(nmemb, size);
	return (ptr);
}
