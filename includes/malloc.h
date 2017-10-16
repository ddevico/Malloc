/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tktorza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 12:02:15 by tktorza           #+#    #+#             */
/*   Updated: 2017/10/03 16:26:35 by ddevico          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <sys/mman.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <stddef.h>
# include <unistd.h>
# include <string.h>
# include <pthread.h>
# include "../libft/includes/libft.h"

# define TINY (size_t)getpagesize() * 2
# define SMALL (size_t)getpagesize() * 16

typedef struct			s_page
{
	size_t				busy;
	size_t				size;
	struct s_block		*block;
	struct s_page		*next;
}						t_page;

typedef struct			s_block
{
	size_t				size;
	size_t				busy;
	struct s_block		*next;
}						t_block;

typedef struct			s_value
{
	size_t				size;
	int					y;
}						t_value;

t_page					*g_page_one;

void					*calloc(size_t nmemb, size_t size);
void					*exec_calloc(size_t nmemb, size_t size);

void					*malloc(size_t size);
void					*exec_malloc(size_t size);
void					malloc_init(void);

void					*realloc(void *ptr, size_t size);
void					*exec_realloc(void *ptr, size_t size);

void					free(void *ptr);
void					exec_free(void *ptr);

int						busy_question(t_page *origin, size_t size);
int						busy_precision(t_page *origin, size_t size);
void					show_alloc_mem(void);
void					show_alloc_mem2(void);
void					put_pointer(void *ptr);
void					dump(int type);

size_t					type_of_size(size_t size);
int						types_of_var(size_t page, size_t size);
void					*memory_plus(void *addr, size_t inc);
void					*busyness(t_page page, size_t size, int busy);
int						busy_increment(int busy);
void					*update_maillon(t_page *page, t_block *one, void *ptr,
						size_t size);

#endif
