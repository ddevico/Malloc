/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chaine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tktorza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/06 15:57:12 by tktorza           #+#    #+#             */
/*   Updated: 2017/09/06 15:57:16 by tktorza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "includes/malloc.h"

//a modifier 
t_page *new_maillon(size_t size, void *address)
{
	t_page *origin;

	origin = mmap(NULL, sizeof(t_page), PROT_WRITE | PROT_READ, MAP_ANON | MAP_PRIVATE, -1, 0);
	origin->busy = size;
	origin->octet = getpagesize() - (size % getpagesize());
	origin->address = mmap(address, size, PROT_WRITE | PROT_READ, MAP_ANON | MAP_PRIVATE, -1, 0);
	origin->next = NULL;

	return (origin);
}

//a modifier 
void	*add_maillon(t_page *one, size_t size, void *address)
{
	while(one->next != NULL)
	{
        printf("stocke busy: %zu | octet %d | address: %p \n", one->busy, one->octet, one->address);
        one = one->next;
    }	
	one->next = new_maillon(size, address);
	return (address);
}

//DAVY faire mm fonctions que les deux precedentes mais pour block

void    *traitement(size_t size, t_page *page_one)
{
    t_page *origin;

    origin = page_one;
    while (origin)
    {
        if (origin->octet >= size)
        {

        }
    }

}

//si free alors deplace bloc au debut de la page libérée
void *my_malloc(size_t size)
{
	static t_page *page_one = NULL;
	t_page *page;

    if (page_one == NULL)
    {
        page_one = new_maillon(size, NULL);
    }

    page = page_one;
    //return (traitement());
    return(add_maillon(page_one, size, mmap(NULL, size, PROT_WRITE | PROT_READ, MAP_ANON | MAP_PRIVATE, -1, 0)));
	
}

int main(int ac, char **av)
{
    unsigned int nb = atoi(av[2]);
    char *str;
    int y = 0;
    int i = 0;

    while (i < nb)
    {
        printf("fois: %d", i);
         str = (char *)my_malloc(((sizeof(char)*strlen(av[1]))*nb)+1);
        int x = 0;
        while (x < strlen(av[1]))
        {
            str[y] = av[1][x];
            y++;
            x++;
        }
    str[y] = '\0';
    printf("%s\n", str);

        i++;
        x=0;
    }
    return (0);

}