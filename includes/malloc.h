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

typedef struct s_page
{
    //nombres d'octets occupés
    size_t     busy;
    //nombre d'octets disponibles dans cette page
    int     octet;
    void    *address;//espace memoire de début
    void    *next;
}             page_t

page_t g_origin;
#endif
