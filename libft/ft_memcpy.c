/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tktorza <tktorza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 13:54:02 by tktorza           #+#    #+#             */
/*   Updated: 2017/09/29 11:51:43 by davydevico       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t		i;
	char		*a;
	const char	*b;

	i = 0;
	a = (char *)dst;
	b = (const char *)src;
	while (i < n)
	{
		a[i] = b[i];
		i++;
	}
	return (dst);
}
