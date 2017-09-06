/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tktorza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/04 14:46:04 by tktorza           #+#    #+#             */
/*   Updated: 2017/09/04 14:46:38 by tktorza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
#define MALLOC_H

#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>
#include <string.h>

typedef struct s_page
{
    size_t  busy;
    size_t  size;
    void    *address;//espace memoire de début
    struct s_page   *next;
    struct s_block  *block;
}             t_page;

typedef struct s_block
{
    size_t  size;
    void    *address;
    struct s_block  *next;
}             t_block;

t_page *page_one;


#endif
