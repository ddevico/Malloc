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

page_t beginning(size_t size)
{
	page_t origin;

	origin = mmap(NULL, sizeof(t_page), PROT_WRITE | PROT_READ, MAP_ANON | MAP_PRIVATE, -1, 0);
	origin.busy = size;
	origin.octet = getpagesize() - (size % getpagesize());
	origin.address = mmap(NULL, size, PROT_WRITE | PROT_READ, MAP_ANON | MAP_PRIVATE, -1, 0);
	origin.next = NULL;

	return (origin);
}

//si free alors deplace bloc au debut de la page libérée
void *my_malloc(size_t size)
{
	static page_t page_one = beginning(size);
	//faire liste chainée
	//tab des octets de libres par page

	void *test;
	if (size < getpagesize())
	{
		while (page)
		{
			if (page->octet >= size)
			{
				return (mmap(page->space + page->busy, size, PROT_WRITE | PROT_READ, MAP_ANON | MAP_PRIVATE, -1, 0))
			}
			page = page->next;
		}
	}
	test = mmap(NULL, size, PROT_WRITE | PROT_READ, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (test != retour erreur mmap)
	{
		return (&test);
	}
}

int main(int argc, char **argv)
{
	//int nb = getpagesize() - 1; //fonctionne
	int nb = (getpagesize() * 2) + 22; //fonctionne pas
	int i = 0;
	char *str;

	//str = (char *)my_malloc(nb);
	while (i < nb - 1)
	{
		str[i] = 'x';
		i++;
	}
	str[i] = '\0';
	printf("%s\n", str);

	int sens = 4000 % 8054;
	int autre = 54 % 4000;
	printf("sens : %d | autre : %d \n", sens, autre);
	return 0;
}