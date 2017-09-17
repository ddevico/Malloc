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

# define TINY 2*getpagesize()
# define SMALL 4*getpagesize()
# define LARGE 8*getpagesize()

typedef struct s_page
{
    size_t  busy;
    size_t  size;
    struct s_block  *block;
    struct s_page   *next;
}             t_page;

typedef struct s_block
{
    size_t  size;
    size_t  busy;
    struct s_block  *next;
}             t_block;

t_page *g_page_one;
void    *my_malloc(size_t size);
void my_free(void *ptr);
void *my_realloc(void *ptr, size_t size);
void *memory_plus(void *addr, size_t inc);
int     busy_question(t_page *origin, size_t size);
int     busy_precision(t_page *origin, size_t size);


#endif
