/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tktorza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/04 14:12:37 by tktorza           #+#    #+#             */
/*   Updated: 2017/09/04 16:21:53 by tktorza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void *my_malloc(size_t size)
{
	//if tiny 
	if (getpagesize() < size)
	{

	}
	//small
	else if (getpagesize() < size && size < getpagesize() * 5)
	{

	}
	//large
	else
	{

	}
	return(mmap(NULL, size, PROT_WRITE | PROT_READ, MAP_ANON | MAP_PRIVATE, -1, 0));
}

int main(int argc, char **argv)
{
	//int nb = getpagesize() - 1; //fonctionne
	int nb = (getpagesize() * 2) +22; //fonctionne pas 
	int i = 0;
	char *str;

	str = (char *)my_malloc(nb);
	while(i < nb-1)
	{
		str[i] = 'x';
		i++;
	}
	str[i] = '\0';
	printf("%s\n", str);
	return 0;
}