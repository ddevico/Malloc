/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddevico <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 15:15:20 by ddevico           #+#    #+#             */
/*   Updated: 2017/09/26 15:56:21 by ddevico          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/malloc.h"

void		*calloc(size_t nmemb, size_t size)
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

int			busy_increment(int busy)
{
	while (g_page_one->block)
	{
		busy += g_page_one->block->busy;
		g_page_one->block = g_page_one->block->next;
	}

	return (busy);
}