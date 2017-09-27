/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tktorza <tktorza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/04 14:46:04 by tktorza           #+#    #+#             */
/*   Updated: 2017/09/26 17:38:54 by ddevico          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <sys/mman.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include <unistd.h>
# include <string.h>
# include "../libft/includes/libft.h"

# define TINY 300
# define SMALL 400
# define LARGE 1000

typedef struct		s_page
{
	size_t			busy;
	size_t			size;
	struct s_block	*block;
	struct s_page	*next;
}					t_page;

typedef struct		s_block
{
	size_t			size;
	size_t			busy;
	struct s_block	*next;
}					t_block;

t_page				*g_page_one;

void				*calloc(size_t nmemb, size_t size);

void				*malloc(size_t size);

void				*realloc(void *ptr, size_t size);

int					busy_question(t_page *origin, size_t size);
int					busy_precision(t_page *origin, size_t size);
void				free(void *ptr);
void				show_alloc_mem(void);

void				impress(void);
size_t				type_of_size(size_t size);
int					types_of_var(size_t page, size_t size);
void				*memory_plus(void *addr, size_t inc);
void				*busyness(t_page page, size_t size, int busy);

#endif
